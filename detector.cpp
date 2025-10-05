#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <regex>

// Define trusted library directories (whitelist)
const std::vector<std::string> trusted_libraries = {
    "/usr/lib/", 
    "/System/Library/Frameworks/", 
    "/System/Library/PrivateFrameworks/",
    "/System/Library/CoreServices/"
};

// Function to check if a library path is trusted
bool is_trusted_library(const std::string& lib_path) {
    for (const auto& prefix : trusted_libraries) {
        if (lib_path.find(prefix) == 0) { // Check if lib_path starts with a trusted prefix
            return true;
        }
    }
    return false;
}

void check_process_libraries(const std::string& process_name) {
    // Get PID using pgrep
    std::string command = "pgrep " + process_name;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "[ERROR] Failed to run pgrep" << std::endl;
        return;
    }

    char buffer[128];
    std::string pid;
    if (fgets(buffer, sizeof(buffer), pipe)) {
        pid = buffer;
        pid.erase(pid.find_last_not_of(" \n\r") + 1);  // Trim newline
    }
    pclose(pipe);

    if (pid.empty()) {
        std::cerr << "[ERROR] No process found with name: " << process_name << std::endl;
        return;
    }

    std::ostringstream vmmap_cmd;
    vmmap_cmd << "vmmap " << pid << " | grep 'dylib'";
    std::string vmmap_command = vmmap_cmd.str();

    FILE* vm_pipe = popen(vmmap_command.c_str(), "r");
    if (!vm_pipe) {
        std::cerr << "[ERROR] Failed to run vmmap on PID: " << pid << std::endl;
        return;
    }

    std::ofstream log_file("detector_log.txt", std::ios::app);
    if (!log_file) {
        std::cerr << "[ERROR] Failed to open log file!" << std::endl;
        return;
    }

    char vm_buffer[4096];
    std::regex lib_regex(R"(\s+(\S+\.dylib))"); // Extracts full library names ending in .dylib

    while (fgets(vm_buffer, sizeof(vm_buffer), vm_pipe) != nullptr) {
        std::string line(vm_buffer);
        // std::cout << "[DEBUG] vmmap output: " << line; // Print raw vmmap output

        std::smatch match;
        if (std::regex_search(line, match, lib_regex)) {
            std::string lib_path = match[1].str();
            // std::cout << "[DEBUG] Extracted library: " << lib_path << std::endl;

            // **New Whitelist Check**
            if (!is_trusted_library(lib_path)) {  
                std::ostringstream alert_msg;
                alert_msg << "[ALERT] Suspicious library loaded: " << lib_path << " in PID " << pid << "\n";

                // Print and log
                std::cout << alert_msg.str();
                log_file << alert_msg.str();
            } else {
                std::cout << "[INFO] Whitelisted library: " << lib_path << std::endl;
            }
        }
    }

    pclose(vm_pipe);
    log_file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <process_name>" << std::endl;
        return 1;
    }

    check_process_libraries(argv[1]);
    return 0;
}
