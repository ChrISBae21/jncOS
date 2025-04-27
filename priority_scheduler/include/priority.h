#ifndef PRIORITY_H
#define PRIORITY_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PRIORITY_LEVELS 8

/* Task structs will hold related info to individual task as well as following task to make 
 * scheduling easy. Ex: sp, reg context, and address of next and prev task.
 * */

typedef struct task{
    char symbol;
    uint8_t priority_level;    
    struct task* nextTask;
} task; 

typedef struct rr_wrapper {
    task* head;
    task* tail;
} rr_wrapper;

extern rr_wrapper pl_array[PRIORITY_LEVELS];

void ps_admit(task* task);
void ps_remove(task* task);
task* ps_next(void);

#endif
