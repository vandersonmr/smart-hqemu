#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>
#include "tracer.h"
#include "utils.h"
#include "llvm.h"
#include "llvm-target.h"
#include "llvm-soft-perfmon.h"
#include "metrics.h"
#include "AOSPasses.h"

static RegionProfiler METRICS;

RegionProfiler::RegionProfiler()
{
}

RegionProfiler::~RegionProfiler()
{
    for (auto metric = metrics.begin(); metric != metrics.end(); metric++)
        delete metric->second;
    metrics.clear();
}

void RegionProfiler::increment_num_executions(uint64_t address, int inc = 1)
{
    RegionMetadata* region = get_or_create_region_data(address);
    region->num_executions += inc;
}

void RegionProfiler::increment_num_compilations(uint64_t address, int inc = 1)
{
    RegionMetadata* region = get_or_create_region_data(address);
    region->num_compilations += inc;
}

void RegionProfiler::increment_exec_time(uint64_t address, uint64_t val)
{
    RegionMetadata* region = get_or_create_region_data(address);
    region->execution_time += val;
}

void RegionProfiler::increment_comp_time(uint64_t address, uint64_t val)
{
    RegionMetadata* region = get_or_create_region_data(address);
    region->compilation_time += val;
}

void RegionProfiler::set_optimizations(uint64_t address, uint16_t* vals) {
    RegionMetadata* region = get_or_create_region_data(address);
    region->optimizations = vals;
}

void RegionProfiler::set_DNA(uint64_t address, std::string vals) {
    RegionMetadata* region = get_or_create_region_data(address);
    region->DNA = vals;
}

void RegionProfiler::print(void)
{
    auto &OS = DM.debug();
    OS  << "\nMetrics statistics: \n";
    OS << "DNA;Region;ExecutionTime;#Executed;CompilationTime;#Compilated;OPTSet\n";
    for (auto metric = metrics.begin(); metric != metrics.end(); metric++)
    {
        char addr[16];
        auto region_data = metric->second;
        std::sprintf(addr, "%lx", region_data->address);
        OS  << region_data->DNA << ";"
            << addr << ";"
            << region_data->execution_time << ";"
            << region_data->num_executions << ";"
            << region_data->compilation_time << ";"
            << region_data->num_compilations << ";";

        OS  << "[";
        if (region_data->optimizations)
        {
            int i = 0;
            while(1){
                OS << region_data->optimizations[i];
                if (region_data->optimizations[i])
                    OS << ",";
                else
                    break;
                i++;
            }
        }
        OS  << "]\n";
    }
}

RegionMetadata* RegionProfiler::get_or_create_region_data(uint64_t address)
{
    if (metrics.find(address) == metrics.end())
        metrics[address] = new RegionMetadata(address);
    return metrics[address];
}

extern "C" {
    // void* metrics_create(void)
    // {
    //     return reinterpret_cast<void*>(new RegionProfiler());
    // }
    //
    // void metrics_delete(void* data)
    // {
    //     if (!data)
    //         return;
    //
    //     RegionProfiler* prof = reinterpret_cast<RegionProfiler*>(data);
    //     delete prof;
    // }

    void increment_num_executions(uint64_t address)
    {
        METRICS.increment_num_executions(address, 1);
    }

    void increment_num_compilations(uint64_t address)
    {
        METRICS.increment_num_compilations(address, 1);
    }

    void increment_exec_time(uint64_t address, uint64_t val)
    {

        METRICS.increment_exec_time(address, val);
    }

    void increment_comp_time(uint64_t address, uint64_t val)
    {
        METRICS.increment_comp_time(address, val);
    }

    void set_optimizations(uint64_t address, uint16_t* vals)
    {
        METRICS.set_optimizations(address, vals);
    }

    void set_DNA(uint64_t address, const char* vals)
    {
        METRICS.set_DNA(address, std::string(vals));
    }

    void metric_print(void)
    {
        METRICS.print();
    }

    unsigned long long get_ticks(void)
    {
        uint64_t rax,rdx,aux;
        asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
        return (rdx << 32) + rax;
    }

}
