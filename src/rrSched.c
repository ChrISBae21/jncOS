#include "rr_sched.h"


#include <stddef.h>
#include <stdio.h>

#define STACK_SIZE 1024


static Job head = NULL;
static Job tail = NULL;
static int jobCount = 0;


void rr_admit(Job newJob) {
    /* scheduler not initialized */
    if(jobCount == 0) {
        head = newJob;
        tail = newJob;
        newJob->nextJob = newJob;
    }
    /* jobs already in the scheduler, append to the end */
    else {
        newJob->nextJob = tail->nextJob;
        tail->nextJob = newJob;
        tail = newJob;
    }
    
    jobCount++;
}

void rr_remove(Job rem_job) {
    Job current;
    /* if the head is the only one in the scheduler */
    if( (head == tail) && (head == rem_job) ) {
        tail = NULL;
        head = NULL;
    }
    /* if removing the head */
    else if (head == rem_job){
        head = rem_job->nextJob;
        tail->nextJob = head;
    }
    /* multiple jobs in the scheduler*/
    else {
        current = head;
        /* iterate through the list of jobs */
        while(current->nextJob != rem_job) {
            current = current->nextJob;
            if (current == tail){
                return;
            }
        }
        /* if removing the tail */
        if(current->nextJob == tail) {
            tail = current;        
        }
        /* change pointer references */
        current->nextJob = rem_job->nextJob;
    }
    
    jobCount--;
}

Job rr_next(void) {
    Job nextjob;
    if(head == NULL) {
        return NULL;
    }
    /* shift over the next Job to be run */
    nextjob = head;
    tail = tail->nextJob;
    head = head->nextJob;
    return nextjob;
}

int rr_qlen(void) {
    return jobCount;
}
