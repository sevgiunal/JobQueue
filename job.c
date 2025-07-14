/*
 * Replace the following string of 0s with your student number
 * 20055429
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "job.h"

/* 
 * DO NOT EDIT the job_new function.
 */
job_t* job_new(pid_t pid, unsigned int id, unsigned int priority, 
    const char* label) {
    return job_set((job_t*) malloc(sizeof(job_t)), pid, id, priority, label);
}

/* 
 * TODO: you must implement this function
 */
job_t* job_copy(job_t* src, job_t* dst) { 
    if (src==NULL)
		return NULL; 

    else if (dst==src)
		return src;
    
    else if (dst==NULL)
    {job_t* newjob = job_new(src -> pid, src -> id, src -> priority, src -> label);
		
		if (strnlen(src->label, MAX_NAME_SIZE) !=MAX_NAME_SIZE-1)
			return NULL;
	
    return newjob;} 


    else if (dst!=NULL && dst!=src)
    {*dst = *src;

		if(strnlen(src->label, MAX_NAME_SIZE) !=MAX_NAME_SIZE-1){
			return NULL;}
			
    return dst;}
	
	return NULL;
}

/* 
 * TODO: you must implement this function
 */
void job_init(job_t* job) {
	if(job != NULL ){
		job->pid=0;
		job->id=0;
		job->priority=0;
		snprintf((job->label),MAX_NAME_SIZE, "%s%s", "", PAD_STRING); }
}

/* 
 * TODO: you must implement this function
 */
bool job_is_equal(job_t* j1, job_t* j2) { 
			
	if((j1 == NULL && j2 != NULL) || (j1 != NULL && j2 == NULL))
		return false;
	
	
	else if((j1 == NULL && j2 == NULL) || (j1->pid == j2->pid && j1->id == j2->id && j1->priority == j2->priority && strncmp(j1->label,j2->label, 32)==0))
		return true;
	
			
	return false;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - read the information in job.h about padding and truncation of job
 *      labels
 */
job_t* job_set(job_t* job, pid_t pid, unsigned int id, unsigned int priority,
    const char* label) {
	if( job != NULL){
		job -> pid = pid;
		job -> id = id;
		job -> priority = priority;
		if (label == 0)
			label = "";
		
		snprintf((job->label),MAX_NAME_SIZE, "%s%s", label, PAD_STRING);
	}	
    return job;
}

/*

 * TODO: you must implement this function.
 * Hint:
 * - see malloc and calloc system library functions for dynamic allocation, 
 *      and the documentation in job.h for when to do dynamic allocation
 */
char* job_to_str(job_t* job, char* str) {
	if (!job || strnlen(job->label, MAX_NAME_SIZE) !=MAX_NAME_SIZE-1) 
		return NULL;
	
	
	
	char* stringrep = str != NULL ? str : calloc(JOB_STR_SIZE, sizeof(char));

	
	if (stringrep){

			if(snprintf(stringrep, JOB_STR_SIZE, JOB_STR_FMT, job->pid, job->id, job->priority, job->label) == -1){
				if(stringrep != str){
					free(stringrep);
				}
			return NULL;
			}
		return stringrep;
	}
	return NULL;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - see the hint for job_to_str
 */
job_t* str_to_job(char* str, job_t* job) {
	if(!str || strnlen(str, JOB_STR_SIZE) !=JOB_STR_SIZE-1)
		return NULL;
	
	job_t *jobrep = job ? job : malloc(sizeof(job_t));
	
	if(jobrep){
	
		if(sscanf(str, JOB_STR_FMT, &jobrep->pid, &jobrep->id, &jobrep->priority, jobrep->label) != 4 || strnlen(jobrep->label, MAX_NAME_SIZE) !=MAX_NAME_SIZE-1){
			if(jobrep != job){
				free(jobrep);
			}
			return NULL;
		}
	}	
	return jobrep;
}

/* 
 * TODO: you must implement this function
 * Hint:
 * - look at the allocation of a job in job_new
 */
void job_delete(job_t* job) {
	free(job);
}