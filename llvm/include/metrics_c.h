#include <stdint.h>

// void* metrics_create(void);
// void metrics_delete(void*);
void increment_num_executions(uint64_t);
void increment_num_compilations(uint64_t);
void increment_exec_time(uint64_t, uint64_t);
void increment_comp_time(uint64_t, uint64_t);
void set_optimizations(uint64_t, uint32_t*);
void metric_print(void);

unsigned long long get_ticks(void);
