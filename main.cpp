#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    std::ifstream info("/proc/meminfo");

    if(!info.is_open()) {
        std::cerr << "Failed to open /proc/meminfo" << std::endl;
        return 1;
    }

    std::string line;
    std::string total;
    std::string available;

    while (std::getline(info, line)) {
        if (line.starts_with("MemTotal:")) {
            total = line;
        }
        if (line.starts_with("MemAvailable:")) {
            available = line;
        }
    }
    

    return 0;
}