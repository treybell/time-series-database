#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct MemoryStats {
    long totalKb = -1;
    long availableKb = -1;
};

MemoryStats readMemoryKb() {
    MemoryStats stats{};
    
    std::ifstream info("/proc/meminfo");

    if(!info.is_open()) {
        std::cerr << "Failed to open /proc/meminfo" << std::endl;
        return MemoryStats{};
    }

    std::string line;
    std::string label;
    

    while (std::getline(info, line)) {
        if (line.starts_with("MemTotal:")) {
            std::stringstream stream(line);
            stream >> label >> stats.totalKb;
        }
        if (line.starts_with("MemAvailable:")) {
            std::stringstream stream(line);
            stream >> label >> stats.availableKb;
        }
    }


    return stats;
    
   
}



int main() {
    
    MemoryStats stats = readMemoryKb();

    std::cout << "usedMb:" << (stats.totalKb - stats.availableKb) / 1024 << "\n";

    return 0;
}