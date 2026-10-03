#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include "metrics.hpp"

//need to add checks and throws later
CpuStats readCpuTimes() {
    CpuStats stats{};
    
    std::ifstream info("/proc/stat");

    if (!info.is_open()) {
        std::cerr << "Failed to open /proc/stat" << "\n";
        return CpuStats{};
    }

    std::string line;
    long temp;
    long total = 0L;
    long idle = 0L;
    std::string label;

    
        
    std::getline(info, line);
               

    std::stringstream stream(line);
    stream >> label;
    stream >> temp; total += temp;
    stream >> temp; total += temp;
    stream >> temp; total += temp;
    stream >> temp; total += temp; idle += temp;
    stream >> temp; total += temp; idle += temp;
    stream >> temp; total += temp;
    stream >> temp; total += temp;
    stream >> temp; total += temp;

    stats.total = total;
    stats.idle = idle;
                
    return stats;
    
 
}

   double computeCpuUsage(const CpuStats& prev, const CpuStats& curr) {
        double total = 0.0;
        double idle = 0.0;
        double nonIdle = 0.0;
        double cpuUsage = 0.0;

        total = curr.total - prev.total;
        idle = curr.idle - prev.idle;
        nonIdle = total - idle;
        if (total == 0.0) {
            return 0.0;
        }
        cpuUsage = nonIdle / total * 100;

        return cpuUsage;
        
    }




MemoryStats readMemoryKb() {
    MemoryStats stats{};
    
    std::ifstream info("/proc/meminfo");

    if(!info.is_open()) {
        std::cerr << "Failed to open /proc/meminfo" << "\n";
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