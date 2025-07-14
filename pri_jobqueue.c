/*
 * Replace the following string of 0s with your student number
 * 20055429
 */
#include <stdlib.h>
#include <stdbool.h>
#include "pri_jobqueue.h"

/* 
 * TODO: you must implement this function that allocates a job queue and 
 * initialise it.
 * Hint:
 * - see job_new in job.c
 */
pri_jobqueue_t* pri_jobqueue_new() {
	pri_jobqueue_t* pjq = (pri_jobqueue_t*) malloc(sizeof(pri_jobqueue_t));
	
	pri_jobqueue_init(pjq);
	
   return pjq;
}

/* 
 * TODO: you must implement this function.
 */
void pri_jobqueue_init(pri_jobqueue_t* pjq) {
	
	pjq -> buf_size = JOB_BUFFER_SIZE;
	pjq -> size = 0;
		
	for(int i = 0; i < pjq-> buf_size; i++)
		job_init(&pjq -> jobs[i]);
		
}

/* 
 * TODO: you must implement this function.
 * Hint:
 *      - if a queue is not empty, and the highest priority job is not in the 
 *      last used slot on the queue, dequeueing a job will result in the 
 *      jobs on the queue having to be re-arranged
 *      - remember that the job returned by this function is a copy of the job
 *      that was on the queue
 */
job_t* pri_jobqueue_dequeue(pri_jobqueue_t* pjq, job_t* dst) {
	if(pri_jobqueue_is_empty(pjq) || pjq-> jobs[0].priority == 0)
		return NULL;
	
	dst = job_copy(&pjq-> jobs[pjq -> size -1], dst);
	
	if(dst != NULL){
		job_init(&pjq -> jobs[pjq-> size -1]);
		pjq-> size --;
	}
	
	return dst;
	
}
	



/* 
 * TODO: you must implement this function.
 * Hints:
 * - if a queue is not full, and if you decide to store the jobs in 
 *      priority order on the queue, enqueuing a job will result in the jobs 
 *      on the queue having to be re-arranged. However, it is not essential to
 *      store jobs in priority order (it simplifies implementation of dequeue
 *      at the expense of extra work in enqueue). It is your choice how 
 *      you implement dequeue (and enqueue) to ensure that jobs are dequeued
 *      by highest priority job first (see pri_jobqueue.h)
 * - remember that the job passed to this function is copied to the 
 *      queue
 */
void pri_jobqueue_enqueue(pri_jobqueue_t* pjq, job_t* job) {
	if(job == NULL || pjq == NULL || pjq-> size == pjq-> buf_size || job -> priority == 0|| pri_jobqueue_is_full(pjq)){
		return;
	}
	
	int top = pjq->size;	
	
	for (int i = 0; i < pjq->size; i++) {
		if (pjq->jobs[i].priority <= job->priority) {
			top = i;
			break;
		}
	}
	
	for (int i = pjq->size - 1; i > top - 1; i--)
		pjq->jobs[i + 1] = pjq->jobs[i];

	job_copy(job, &pjq -> jobs[top]);
	pjq->size++;
		
}
	
/* 
 * TODO: you must implement this function.
 */
bool pri_jobqueue_is_empty(pri_jobqueue_t* pjq) {
	if(pjq == NULL|| pjq -> size == 0)
		return true;
	
	
	return false;
}

/* 
 * TODO: you must implement this function.
 */
bool pri_jobqueue_is_full(pri_jobqueue_t* pjq) {
	if(pjq == NULL || pjq -> size == pjq -> buf_size)
		return true;
	
	
	return false;
}

/* 
 * TODO: you must implement this function.
 * Hints:
 *      - remember that the job returned by this function is a copy of the 
 *      highest priority job on the queue.
 *      - both pri_jobqueue_peek and pri_jobqueue_dequeue require copying of 
 *      the highest priority job on the queue
 */
job_t* pri_jobqueue_peek(pri_jobqueue_t* pjq, job_t* dst) {
    if (pjq == NULL || pjq->size == 0 || pjq->jobs[pjq->size - 1].pid < 0  
        || pjq->jobs[pjq->size - 1].priority == 0)
        return NULL;
		
		
		
	else if(dst != NULL){
		*dst = pjq->jobs[pjq->size - 1];
		return dst;
	}


	else if(dst == NULL){
		job_t* new_job = malloc(sizeof(job_t));
		*new_job = pjq->jobs[pjq->size - 1];
		return new_job;
	}

	return NULL;
}

/* 
 * TODO: you must implement this function.
 */
int pri_jobqueue_size(pri_jobqueue_t* pjq) {
	if(pjq == NULL)
		return 0;
	
    return pjq -> size;
}

/* 
 * TODO: you must implement this function.
 */
int pri_jobqueue_space(pri_jobqueue_t* pjq) {
	int space = 0;
	if(pri_jobqueue_is_full(pjq)){
		space = 0;
	}else {
		space = pjq -> buf_size - pjq -> size;
	}

	return space;
}

/* 
 * TODO: you must implement this function.
 *  Hint:
 *      - see pri_jobqeue_new
 */
void pri_jobqueue_delete(pri_jobqueue_t* pjq) {
	free(pjq);
}
