/*
 * student.c
 * Multithreaded OS Simulation for CS 2200, Project 5
 * Fall 2016
 *
 * This file contains the CPU scheduler for the simulation.
 * Name: Shyam Natarajan
 * GTID: 903047415
 */

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os-sim.h"


/*
 * current[] is an array of pointers to the currently running processes.
 * There is one array element corresponding to each CPU in the simulation.
 *
 * current[] should be updated by schedule() each time a process is scheduled
 * on a CPU.  Since the current[] array is accessed by multiple threads, you
 * will need to use a mutex to protect it.  current_mutex has been provided
 * for your use.
 */
static pcb_t **current;
static pthread_mutex_t current_mutex;

static int timeslice;
static int type = 0;
static int cpu_count;

static pthread_mutex_t ready_queue_mutex;

static pcb_t* ready_queue = NULL;
pthread_cond_t not_empty;

static pcb_t* pop_fifo() {
  pthread_mutex_lock(&ready_queue_mutex);
  pcb_t* temp = ready_queue;
  if (ready_queue != NULL) {
    ready_queue = ready_queue->next;
    temp->next = NULL;
  }
  pthread_mutex_unlock(&ready_queue_mutex);
  return temp;
}

static pcb_t* pop_static() {
  pthread_mutex_lock(&ready_queue_mutex);
  pcb_t* temp = ready_queue;
  pcb_t* output = ready_queue;
  pcb_t* prev = ready_queue;
  pcb_t* four = ready_queue;
  if (ready_queue != NULL) {
    if (ready_queue->next != NULL) {
      temp = ready_queue->next;
      if (temp->static_priority > output->static_priority) {
        output = temp;
        four = prev;
      }
      temp = temp->next;
      prev = prev->next;
    }
    if (output == ready_queue) {
      ready_queue = ready_queue->next;
    } else {
      four->next = output->next;
    }
  }
  pthread_mutex_unlock(&ready_queue_mutex);
  return output;
}

static void push(pcb_t* pcb) {
  pthread_mutex_lock(&ready_queue_mutex);
  pcb->state = PROCESS_READY;
  if (ready_queue == NULL) {
    ready_queue = pcb;
    ready_queue->next = NULL;
  } else {
    pcb_t* temp = ready_queue;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = pcb;
    pcb->next = NULL;
  }
  pthread_cond_signal(&not_empty);
  pthread_mutex_unlock(&ready_queue_mutex);
}

/*
 * schedule() is your CPU scheduler.  It should perform the following tasks:
 *
 *   1. Select and remove a runnable process from your ready queue which
 *	you will have to implement with a linked list or something of the sort.
 *
 *   2. Set the process state to RUNNING
 *
 *   3. Call context_switch(), to tell the simulator which process to execute
 *      next on the CPU.  If no process is runnable, call context_switch()
 *      with a pointer to NULL to select the idle process.
 *	The current array (see above) is how you access the currently running
 *	process indexed by the cpu id. See above for full description.
 *	context_switch() is prototyped in os-sim.h. Look there for more information
 *	about it and its parameters.
 */
static void schedule(unsigned int cpu_id)
{
    /* FIX ME */
    pcb_t* temp;
    if (type == 2) {
      temp = pop_static();
    } else if (!type || type == 1) {
      temp = pop_fifo();
    }

    if (temp != NULL) {
      temp->state = PROCESS_RUNNING;
    }
    pthread_mutex_lock(&current_mutex);
    *(current + cpu_id) = temp;
    pthread_mutex_unlock(&current_mutex);

    context_switch(cpu_id, temp, timeslice);
}


/*
 * idle() is your idle process.  It is called by the simulator when the idle
 * process is scheduled.
 *
 * This function should block until a process is added to your ready queue.
 * It should then call schedule() to select the process to run on the CPU.
 */
extern void idle(unsigned int cpu_id)
{
    /* FIX ME */
    pthread_mutex_lock(&ready_queue_mutex);
    while (ready_queue == NULL) {
      pthread_cond_wait(&not_empty, &ready_queue_mutex);
    }
    pthread_mutex_unlock(&ready_queue_mutex);
    schedule(cpu_id);
    /*
     * REMOVE THE LINE BELOW AFTER IMPLEMENTING IDLE()
     *
     * idle() must block when the ready queue is empty, or else the CPU threads
     * will spin in a loop.  Until a ready queue is implemented, we'll put the
     * thread to sleep to keep it from consuming 100% of the CPU time.  Once
     * you implement a proper idle() function using a condition variable,
     * remove the call to mt_safe_usleep() below.
     */
}


/*
 * preempt() is the handler called by the simulator when a process is
 * preempted due to its timeslice expiring.
 *
 * This function should place the currently running process back in the
 * ready queue, and call schedule() to select a new runnable process.
 */
extern void preempt(unsigned int cpu_id)
{
    /* FIX ME */
    pthread_mutex_lock(&current_mutex);
    pcb_t* temp = *(current + cpu_id);
    pthread_mutex_unlock(&current_mutex);
    if (temp != NULL) {
      temp->state = PROCESS_READY;
      push(temp);
    }
    schedule(cpu_id);
}


/*
 * yield() is the handler called by the simulator when a process yields the
 * CPU to perform an I/O request.
 *
 * It should mark the process as WAITING, then call schedule() to select
 * a new process for the CPU.
 */
extern void yield(unsigned int cpu_id)
{
    /* FIX ME */
    pthread_mutex_lock(&current_mutex);
    pcb_t *yielder = *(current + cpu_id);
    if (yielder != NULL) {
      yielder->state = PROCESS_WAITING;
    }
    pthread_mutex_unlock(&current_mutex);
    schedule(cpu_id);
}


/*
 * terminate() is the handler called by the simulator when a process completes.
 * It should mark the process as terminated, then call schedule() to select
 * a new process for the CPU.
 */
extern void terminate(unsigned int cpu_id)
{
    /* FIX ME */
    pthread_mutex_lock(&current_mutex);
    pcb_t *terminal = *(current + cpu_id);
    if (terminal != NULL) {
      terminal->state = PROCESS_TERMINATED;
    }
    pthread_mutex_unlock(&current_mutex);
    schedule(cpu_id);
}


/*
 * wake_up() is the handler called by the simulator when a process's I/O
 * request completes.  It should perform the following tasks:
 *
 *   1. Mark the process as READY, and insert it into the ready queue.
 *
 *   2. If the scheduling algorithm is static priority, wake_up() may need
 *      to preempt the CPU with the lowest priority process to allow it to
 *      execute the process which just woke up.  However, if any CPU is
 *      currently running idle, or all of the CPUs are running processes
 *      with a higher priority than the one which just woke up, wake_up()
 *      should not preempt any CPUs.
 *	To preempt a process, use force_preempt(). Look in os-sim.h for
 * 	its prototype and the parameters it takes in.
 */
extern void wake_up(pcb_t *process)
{
    /* FIX ME */
    push(process);

    if (type == 2) {
      pthread_mutex_lock(&current_mutex);
      int locked = 1;
      for (int i = 0; i < cpu_count; i++) {
        if (*(current + i) != NULL) {
          if ((*(current + i))->static_priority < process->static_priority) {
            locked = 0;
            pthread_mutex_unlock(&current_mutex);
            force_preempt(i);
          }
        }/* else {
          push(process);
          locked = 0;
          pthread_mutex_unlock(&current_mutex);
          pthread_cond_signal(&not_empty);
          return;
        }*/
      }
      if (locked) {
        pthread_mutex_unlock(&current_mutex);
      }
    }
    //push(process);
}


/*
 * main() simply parses command line arguments, then calls start_simulator().
 * You will need to modify it to support the -r and -p command-line parameters.
 */
int main(int argc, char *argv[])
{

    /* Parse command-line arguments */
    if (argc == 1)
    {
        fprintf(stderr, "CS 2200 Project 5 Fall 2016 -- Multithreaded OS Simulator\n"
            "Usage: ./os-sim <# CPUs> [ -r <time slice> | -p ]\n"
            "    Default : FIFO Scheduler\n"
            "         -r : Round-Robin Scheduler\n"
            "         -p : Static Priority Scheduler\n\n");
        return -1;
    }
    cpu_count = atoi(argv[1]);

    /* FIX ME - Add support for -r and -p parameters*/
    /********** TODO **************/
    if (argc > 2) {
      if (!strcmp(argv[2], "-r")) {
        type = 1;
      } else if (!strcmp(argv[2], "-p")) {
        type = 2;
      }
    }
    timeslice = -1;

    if (argc == 4) {
      timeslice = atoi(argv[3]);
    }

    /* Allocate the current[] array and its mutex */
    /*********** TODO *************/






    current = malloc(sizeof(pcb_t*) * cpu_count);
    assert(current != NULL);
    pthread_mutex_init(&current_mutex, NULL);

    /* Start the simulator in the library */
    start_simulator(cpu_count);

    return 0;
}
