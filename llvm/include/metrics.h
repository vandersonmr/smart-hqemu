#ifndef __METRICS_H
#define __METRICS_H

//#include <map>
#include <cstdint>
#include "qemu-types.h"
#include "llvm-types.h"
#include "utils.h"
#include "parallel_hashmap/phmap.h"

struct RegionMetadata {
    RegionMetadata(uint64_t address)
                : address(address), num_executions(0), num_compilations(0),
                  execution_time(0), compilation_time(0), optimizations(NULL) {}

    ~RegionMetadata()
    {
        if (optimizations) {
            delete optimizations;
            optimizations = NULL;
        }
    }

    uint64_t address;
    uint64_t num_executions;
    uint32_t num_compilations;
    uint64_t execution_time;
    uint64_t compilation_time;
    uint16_t *optimizations;
    std::string DNA;
};

class RegionProfiler {
    phmap::flat_hash_map<uint64_t , RegionMetadata*> metrics;

public:
    RegionProfiler(void);
    ~RegionProfiler();

    void increment_num_executions(uint64_t address, int inc);
    void increment_num_compilations(uint64_t address, int inc);
    void increment_exec_time(uint64_t address, uint64_t val);
    void increment_comp_time(uint64_t address, uint64_t val);
    void set_optimizations(uint64_t address, uint16_t* vals);
    void set_DNA(uint64_t address, std::string vals);
    void print(void);

private:
    RegionMetadata* get_or_create_region_data(uint64_t address);
};

// extern "C" void* metrics_create(void);
// extern "C" void metrics_delete(void*);
extern "C" void metric_print();
extern "C" void increment_num_executions(uint64_t);
extern "C" void increment_num_compilations(uint64_t);
extern "C" void increment_exec_time(uint64_t, uint64_t);
extern "C" void increment_comp_time(uint64_t, uint64_t);
extern "C" void set_optimizations(uint64_t, uint16_t*);
extern "C" void set_DNA(uint64_t, const char*);
extern "C" unsigned long long get_ticks(void);
#endif /* __METRICS_H */
