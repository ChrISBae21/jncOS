#include "lwp.h"


#include <stddef.h>
#include <stdio.h>

typedef struct jobinfo_st *job;
typedef struct jobinfo_st {
  tid_t         tid;            /* lightweight process id  */
  unsigned long *stack;         /* Base of allocated stack */
  size_t        stacksize;      /* Size of allocated stack */
  rfile         state;          /* saved registers         */
  unsigned int  status;         /* exited? exit status?    */
} context;


typedef struct job_wrapper {
    
    Job nextJob;
    Job prevJob;
} Job;


typedef struct blocked_list {

} blocked_list;



static job head = NULL;
static job tail = NULL;
static int job_count = 0;


void rr_admit(job new_job) {
    /* scheduler not initialized */
    if(job_count == 0) {
        head = new_job;
        tail = new_job;
        new_job->sched_one = new_job;
    }
    /* jobs already in the scheduler, append to the end */
    else {
        new_job->sched_one = tail->sched_one;
        tail->sched_one = new_job;
        tail = new_job;
    }
    
    job_count++;
}

void rr_remove(job rem_job) {
    job current;
    /* if the head is the only one in the scheduler */
    if( (head == tail) && (head == rem_job) ) {
        tail = NULL;
        head = NULL;
    }
    /* if removing the head */
    else if (head == rem_job){
        head = rem_job->sched_one;
        tail->sched_one = head;
    }
    /* multiple jobs in the scheduler*/
    else {
        current = head;
        /* iterate through the list of jobs */
        while(current->sched_one != rem_job) {
            current = current->sched_one;
            if (current == tail){
                return;
            }
        }
        /* if removing the tail */
        if(current->sched_one == tail) {
            tail = current;        
        }
        /* change pointer references */
        current->sched_one = rem_job->sched_one;
    }
    
    job_count--;
}

job rr_next(void) {
    job nextjob;
    if(head == NULL) {
        return NULL;
    }
    /* shift over the next job to be run */
    nextjob = head;
    tail = tail->sched_one;
    head = head->sched_one;
    return nextjob;
}

int rr_qlen(void) {
    return job_count;
}
