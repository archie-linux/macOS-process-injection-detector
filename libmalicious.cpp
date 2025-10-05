#include <iostream>

__attribute__((constructor))
void inject() {
    std::cout << "[Injected] Malicious library loaded!" << std::endl;
}
