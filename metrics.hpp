#pragma once

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

struct MemoryStats {
    long totalKb = -1;
    long availableKb = -1;
};

CpuStats readCpuTimes();
double computeCpuUsage(const CpuStats& prev, const CpuStats& curr);
MemoryStats readMemoryKb();


