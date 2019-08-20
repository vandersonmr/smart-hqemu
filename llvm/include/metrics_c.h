#include <stdint.h>

void* metrics_create(void);
void metrics_delete(void*);
void increment_num_executions(void*, uint64_t);
void increment_num_compilations(void*, uint64_t);
void increment_exec_time(void*, uint64_t, uint64_t);
void increment_comp_time(void*, uint64_t, uint64_t);
void metric_print(void*);
