// File:	mypthread_t.h

// List all group members' names:
// iLab machine tested on:

#ifndef MYTHREAD_T_H
#define MYTHREAD_T_H

#define _GNU_SOURCE

/* in order to use the built-in Linux pthread library as a control for benchmarking, you have to comment the USE_MYTHREAD macro */
#define USE_MYTHREAD 1

/* include lib header files that you need here: */
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <pthread.h>

typedef unsigned int uint;

typedef uint mypthread_t;

	/* add important states in a thread control block */
typedef struct threadControlBlock
{
	// YOUR CODE HERE	
	int Id;
	int status;
	int priority;
	ucontext_t context;
	char threadStack[16384];
	uint waitCalledBy;
	int quantumCount;
	// thread Id
	// thread status
	// thread context
	// thread stack
	// thread priority
	// And more ...

} tcb;

/* mutex struct definition */
typedef struct mypthread_mutex_t
{

	// YOUR CODE HERE
	uint lock;
	mypthread_t owner;
	struct Queue* waitQueue; 
	
} mypthread_mutex_t;

/* mutex struct definition 
typedef struct rpthread_mutex_t {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    Queue<uint> queue;
    uint owner = 0;
} rpthread_mutex_t;*/
// Feel free to add your own auxiliary data structures (linked list or queue etc...)



/* Function Declarations: */

/* create a new thread */
int mypthread_create(mypthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg);

/* current thread voluntarily surrenders its remaining runtime for other threads to use */
int mypthread_yield();

/* terminate a thread */
void mypthread_exit(void *value_ptr);

/* wait for thread termination */
int mypthread_join(mypthread_t thread, void **value_ptr);

/* initialize a mutex */
int mypthread_mutex_init(mypthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);

/* aquire a mutex (lock) */
int mypthread_mutex_lock(mypthread_mutex_t *mutex);

/* release a mutex (unlock) */
int mypthread_mutex_unlock(mypthread_mutex_t *mutex);

/* destroy a mutex */
int mypthread_mutex_destroy(mypthread_mutex_t *mutex);

#ifdef USE_MYTHREAD
#define pthread_t mypthread_t
#define pthread_mutex_t mypthread_mutex_t
#define pthread_create mypthread_create
#define pthread_exit mypthread_exit
#define pthread_join mypthread_join
#define pthread_mutex_init mypthread_mutex_init
#define pthread_mutex_lock mypthread_mutex_lock
#define pthread_mutex_unlock mypthread_mutex_unlock
#define pthread_mutex_destroy mypthread_mutex_destroy
#define pthread_yield mypthread_yield
#endif

#endif
