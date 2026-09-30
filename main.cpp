#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include<thread>
#include "metrics.hpp"


int main() {
    
    
    while (true) {

        
        CpuStats before = readCpuTimes();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        long timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        CpuStats now = readCpuTimes();

        if (before.idle == -1 || before.total == -1 || now.idle == -1 || now.total == -1) {
            std::cerr << "Failed to read CPU stats.";
        } else {
            double usage = computeCpuUsage(before, now);
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