/**
* @author Karel Chanivecky Garcia
* BCIT 2021
*/

#ifndef DC_DATA_STRUCTURES_DC_THREADED_QUEUE_H
#define DC_DATA_STRUCTURES_DC_THREADED_QUEUE_H

#include "pthread.h"
#include "dlinked_list.h"
#include "semaphore.h"

// sem wait
#define DCTQ_ERR_SWAIT -10

// sem post
#define DCTQ_ERR_SPOST -11 //

// mutex init
#define DCTQ_ERR_MXINIT -15

// mutex lock
#define DCTQ_ERR_MXLK -16

// mutex unlock
#define DCTQ_ERR_MXULK -17

struct dc_threaded_queue;

typedef int (*dc_threaded_queue_adder) (struct dc_threaded_queue * queue, void * element) ;
typedef void * (*dc_threaded_queue_popper) (struct dc_threaded_queue * queue);


struct dc_threaded_queue {
    struct dlinked_list_s * list;
    pthread_mutex_t list_mx;
    sem_t * producer_sem;
    size_t producer_sem_id;
    sem_t * consumer_sem;
    size_t consumer_sem_id;
    dc_threaded_queue_adder add;
    dc_threaded_queue_popper take;
};


/**
 * Initialize a new dc_threaded_queue.
 *
 * @param max_size The maximum size admitted by the queue. Will be used to prevent overwhelming the consumer
 * @return A new, empty queue. NULL if memory allocation failed.
 */
struct dc_threaded_queue * dc_threaded_queue_init(size_t max_size);

/**
 * Destroy queue.
 * @param double pointer to the queue to be destroyed. Will set *queue to NULL
 */
void dc_threaded_queue_destroy(struct dc_threaded_queue ** queue);


#endif //DC_DATA_STRUCTURES_DC_THREADED_QUEUE_H
