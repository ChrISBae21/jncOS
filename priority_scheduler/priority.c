#include "priority.h"

/*
 * Priority Scheduler! 
 *
 * Will be organized in a sort of 2 layer hierarchy. Imagine an array where each index is the
 * head of a linked-list. Each node in the linked-list is a runnable task.
 *
 * */

/* TODO 
 *
 * For how it'll run is the System Level thread will act as the scheduler, more or less.
 * You add the system level threa, and it has either its own reserved place on the hierarchy
 * in terms of priority OR is just separate. Anyway, the system thread will be added last and 
 * that's what will handle choosing the next task to run. Interrupts will trigger, preempt the 
 * running task, start running the system level task, and then the system level task chooses 
 * what runs next. 
 *
 *
 * */

/* TODO the whole logic for the scheduler will actually be in one function: run_next. This will 
 * basically just be wrapped by the main or system level thread.
 *
 * */

/* TODO */
/* Run_Next
 * Arguments: none? maybe a quantum? maybe this could be configurable and a part of the task
 * interface. When the scheduler is about to schedule a task, it checks the task struct for a
 * preexisting quantum value. That way, even among priority levels you can have more control
 * over how long each task will run before being preempted. 
 * Desc: This is the true scheduler function. Search for next highest priority task, set it
 * up to run, and then off to the races!
 * it'd basically just call ps_next, set it up, set up timers and shit, then yield. 
 * would prob look like
 *
 * while(1){
 *  Setup stuff here
 *  ps_next()...
 *  yield()...
 * }
 *
 * */



/* Priority Level Array which holds a wrapper struct describing the list at each level */
rr_wrapper pl_array[PRIORITY_LEVELS];
/* TODO function to init the pl_array with all NULLS at head and tail */
/* TODO api parser should handle adding tasks and shit */

/* Admit
 * Arguments: task
 * Desc: Given a thread add it to its corresonding priority level queue.
 * */
void ps_admit(task* task) {
    /* Find matching Priority Level Round Robin list */
    rr_wrapper* task_rr = &pl_array[task->priority_level];

    /* If empty update rr_wrapper head and tail*/
    if (task_rr->head == NULL && task_rr->tail == NULL){
        task_rr->head = task;
        task_rr->tail = task;
    }

    /* Insert task between tail and head */
    task->nextTask = task_rr->head;
    /* Update old tail next to point to added task */
    task_rr->tail->nextTask = task;
    /* Finally, update rr_wrapper tail */
    task_rr->tail = task;
}

/* Delete
 * Arguments: task
 * Desc: Given a thread remove it from its corresponding priority level queue.
 * */
void ps_remove(task* removeTask) {
    task* currentTask;

    /* Find matching Priority Level Round Robin list */
    rr_wrapper *task_rr = &pl_array[removeTask->priority_level];

    /* If task is the only one in the list */
    if ((task_rr->head == removeTask) && (task_rr->head == task_rr->tail)) {
        task_rr->head = NULL;
        task_rr->tail = NULL;
    }
    /* If removing the head */
    else if (task_rr->head == removeTask) {
        /* Move head to its next task */
        task_rr->head = task_rr->head->nextTask;
        /* Make tail point to new head */
        task_rr->tail->nextTask = task_rr->head;
    }
    /* If task is not head and multiple threads in list */
    else {
        currentTask = task_rr->head;
        /* Parse the list of tasks and stop once the current task's next is 
         * the one to be removed */
        while(currentTask->nextTask != removeTask) {
            currentTask = currentTask->nextTask;
            /* Searched whole list, task not found! */
            if (currentTask == task_rr->tail) {
                return;
            }
        }
        /* If removing the tail */
        if (currentTask->nextTask == task_rr->tail) {
            task_rr->tail = currentTask;
        }

        /* update current to point to removed task's next */
        currentTask->nextTask = removeTask->nextTask;
    }
    
}

/* TODO need yield and blocking for synchronization and shit */

/* Next
 * Arguments: void
 * Desc: Return the next task to be run.
 * 
 *
 * */
task* ps_next(void) {
    task* nextTask = NULL;
    int i;
    rr_wrapper* task_rr;
    /* Search from highest to lowest priority level */
    for (i = (PRIORITY_LEVELS-1); i > 0; i--) {
        task_rr = &pl_array[i];
        /* Check if this level doesn't have a next runnable task */
        if (task_rr->head == NULL){
            continue;
        }
        /* If there is a head, grab it then shift the old head and tail */
        nextTask = task_rr->head;
        task_rr->head = task_rr->head->nextTask;
        task_rr->tail = task_rr->tail->nextTask;
        /* return the task to be run */
        return nextTask;
    }

    /* No tasks exist, return NULL */
    return NULL;
}

// Function to print the priority scheduler in a visual format
void print_scheduler() {
    task* originalHead;
    for (int i = 0; i < PRIORITY_LEVELS; i++) {
        rr_wrapper* task_rr = &pl_array[i];
        if (task_rr->head == NULL) {
            printf("Priority %d: (empty)\n", i);
        }
        else {
            originalHead = task_rr->head;
            printf("Priority %d: ", i);
            task* current = task_rr->head;
            printf("TAIL -> %c -> ", current->symbol);
            current = current->nextTask;
            while (current != originalHead) {
                printf("%c -> ", current->symbol);
                current = current->nextTask;
            }
            printf("HEAD\n");
        }
    }
}

// Helper function to create a new task
task* create_task(char symbol, uint8_t priority) {
    /* TODO still need custom malloc but tasks will be stored in reserved memory */
    task* new_task = (task*)malloc(sizeof(task));
    new_task->symbol = symbol;
    new_task->priority_level = priority;
    new_task->nextTask = NULL;
    return new_task;
}

// Test harness function
void test_scheduler() {
    // Seed random number generator
    srand(time(NULL));
    
    // Create tasks
    task* t1 = create_task('A', 3);
    task* t2 = create_task('B', 5);
    task* t3 = create_task('C', 3);
    task* t4 = create_task('D', 1);
    task* t5 = create_task('E', 5);
    task* t6 = create_task('F', 5);
    
    // Admit tasks to scheduler
    printf("Admitting tasks:\n");
    ps_admit(t1);
    ps_admit(t2);
    ps_admit(t3);
    ps_admit(t4);
    ps_admit(t5);
    ps_admit(t6);
    print_scheduler();
    
    // Call ps_next and show next task
    printf("\nNext task to run: %c\n", ps_next()->symbol);
    print_scheduler();
    printf("Next task to run: %c\n", ps_next()->symbol);
    print_scheduler();
    printf("Next task to run: %c\n", ps_next()->symbol);
    
    // Remove task B (priority 5)
    printf("\nRemoving task B:\n");
    ps_remove(t2);
    print_scheduler();
    
    // Call ps_next again
    printf("\nNext task to run: %c\n", ps_next()->symbol);
    
    // Remove task A (priority 3)
    printf("\nRemoving task A:\n");
    ps_remove(t1);
    print_scheduler();
    
    // Call ps_next again
    printf("\nNext task to run: %c\n", ps_next()->symbol);
}

int main() {
    // Initialize the scheduler's priority levels to NULL
    for (int i = 0; i < PRIORITY_LEVELS; i++) {
        pl_array[i].head = NULL;
        pl_array[i].tail = NULL;
    }
    
    // Run the test harness
    test_scheduler();
    
    return 0;
}
