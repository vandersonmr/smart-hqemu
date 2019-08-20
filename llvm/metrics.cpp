#include <iostream>
#include <sstream>
#include "tracer.h"
#include "utils.h"
#include "llvm.h"
#include "llvm-target.h"
#include "llvm-soft-perfmon.h"
#include "metrics.h"


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

void RegionProfiler::print(void)
{
    auto &OS = DM.debug();
    OS  << "\nMetrics statistics: \n";
    OS << "Region;ExecutionTime;#Executed;CompilationTime;#Compilated\n";
    for (auto metric = metrics.begin(); metric != metrics.end(); metric++)
    {
        auto region_data = metric->second;
        OS  << region_data->address << ";"
            << region_data->execution_time << ";"
            << region_data->num_executions << ";"
            << region_data->compilation_time << ";"
            << region_data->num_compilations << "\n";
    }
}

RegionMetadata* RegionProfiler::get_or_create_region_data(uint64_t address)
{
    if (metrics.find(address) == metrics.end())
        metrics[address] = new RegionMetadata(address);
    return metrics[address];
}

extern "C" {
    void* metrics_create(void)
    {
        return reinterpret_cast<void*>(new RegionProfiler());
    }

    void metrics_delete(void* data)
    {
        if (!data)
            return;

        RegionProfiler* prof = reinterpret_cast<RegionProfiler*>(data);
        delete prof;
    }

    void increment_num_executions(void* data, uint64_t address)
    {
        if (!data)
            return;
        RegionProfiler* prof = reinterpret_cast<RegionProfiler*>(data);
        prof->increment_num_executions(address, 1);
    }

    void increment_num_compilations(void* data, uint64_t address)
    {
        if (!data)
            return;
        RegionProfiler* prof = reinterpret_cast<RegionProfiler*>(data);
        prof->increment_num_compilations(address, 1);
    }

    void increment_exec_time(void* data, uint64_t address, uint64_t val)
    {
        if (!data)
            return;
        RegionProfiler* prof = reinterpret_cast<RegionProfiler*>(data);
        prof->increment_exec_time(address, val);
    }

    void increment_comp_time(void* data, uint64_t address, uint64_t val)
    {
        if (!data)
            return;
        RegionProfiler* prof = reinterpret_cast<RegionProfiler*>(data);
        prof->increment_comp_time(address, val);
    }

    void metric_print(void* data)
    {
        if(!data)
            return;
        RegionProfiler* prof = reinterpret_cast<RegionProfiler*>(data);
        prof->print();
    }
}
