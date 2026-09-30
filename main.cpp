#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include<thread>

struct CpuStats {
    long idle = -1;
    long total = -1;
};


//need to add checks and throws later
CpuStats readCpuTimes() {
    CpuStats stats{};
    
    std::ifstream info("/proc/stat");

    if (!info.is_open()) {
        std::cerr << "Failed to open /proc/stat" << std::endl;
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
    
    
    while (true) {

        
        CpuStats before = readCpuTimes();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        long timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        CpuStats now = readCpuTimes();

        if (before.idle == -1 || before.total == -1 || now.idle == -1 || now.total == -1) {
            std::cerr << "Failed to read CPU stats.";
        } else {
            usage = computeCpuUsage(before, now);
            std::cout << timestamp << " " << "cpu.usage_pct " << usage << "\n";
        }
        
        
        MemoryStats stats = readMemoryKb();
        if (stats.availableKb == -1 || stats.totalKb == -1) {
            std::cerr << "Failed to read memory stats.";
        } else {
            std::cout << timestamp << " " << "mem.used_mb " << (stats.totalKb - stats.availableKb) / 1024 << "\n";
            std::cout << timestamp << " " << "mem.total_mb " << stats.totalKb / 1024 << "\n";
        }
    }
    
    

    

    return 0;
}