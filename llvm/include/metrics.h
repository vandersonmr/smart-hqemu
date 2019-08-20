#ifndef __METRICS_H
#define __METRICS_H

#include <unordered_map>
#include <cstdint>
#include "qemu-types.h"
#include "llvm-types.h"
#include "utils.h"

struct RegionMetadata {
    RegionMetadata(uint64_t address)
                : address(address), num_executions(0), num_compilations(0),
                  execution_time(0), compilation_time(0) {}

    uint64_t address;
    uint64_t num_executions;
    uint32_t num_compilations;
    uint64_t execution_time;
    uint64_t compilation_time;
};

class RegionProfiler {
    std::unordered_map<uint64_t , RegionMetadata*> metrics;

public:
    RegionProfiler(void);
    ~RegionProfiler();

    void increment_num_executions(uint64_t address, int inc);
    void increment_num_compilations(uint64_t address, int inc);
    void increment_exec_time(uint64_t address, uint64_t val);
    void increment_comp_time(uint64_t address, uint64_t val);
    void print(void);

private:
    RegionMetadata* get_or_create_region_data(uint64_t address);
};

extern "C" void* metrics_create(void);
extern "C" void metrics_delete(void*);
extern "C" void metric_print(void*);
extern "C" void increment_num_executions(void*, uint64_t);
extern "C" void increment_num_compilations(void*, uint64_t);
extern "C" void increment_exec_time(void*, uint64_t, uint64_t);
extern "C" void increment_comp_time(void*, uint64_t, uint64_t);

#endif /* __METRICS_H */