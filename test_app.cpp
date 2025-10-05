#include <iostream>
#include <dlfcn.h>
#include <unistd.h> 

int main() {
    void* handle = dlopen("./libmalicious.dylib", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
        return 1;
    }
    
    std::cout << "Library injected successfully." << std::endl;

    sleep(30);  // Keeps the process alive for 30 seconds

    dlclose(handle);
    return 0;
}
