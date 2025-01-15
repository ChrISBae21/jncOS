typedef struct jobinfo_st *job_t;   /* pointer to the struct */
typedef struct jobinfo_st {
  tid_t         tid;            /* lightweight process id  */
  unsigned long *stack;         /* Base of allocated stack */
  uint8_t       state;          /* saved registers (used to be rfile) */
  unsigned int  status;         /* exited? exit status?    */
} context;


typedef struct job_wrapper {
    job_t jobInfo;
    Job nextJob;
    Job prevJob;
} Job;


typedef struct blocked_list {

} blocked_list;


void rr_admit(Job newJob);
void rr_remove(Job rem_job);
Job rr_next(void);
int rr_qlen(void);