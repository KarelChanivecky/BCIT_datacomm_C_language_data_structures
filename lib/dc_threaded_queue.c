/**
* karel on 2021-04-10.
*/

#include <errno.h>
#include <stdlib.h>
#include "dc_threaded_queue.h"
#include "stdio.h"
#include "fcntl.h"

#define DC_THREADED_QUEUE_SEM_NAME "/dc_threaded_queue_%zu_sem"


static size_t queue_counter = 0;

void get_sem_name( char buff[255], size_t val ) {
    sprintf( buff, DC_THREADED_QUEUE_SEM_NAME, val );
}

sem_t * open_sem( size_t value, size_t * id ) {
    sem_t * new_sem = NULL;

    size_t initial_counter = queue_counter;

    while ( !new_sem ) {
        char name[255] = { 0 };
        get_sem_name( name, queue_counter );

        new_sem = sem_open( name, O_CREAT, 0640, value );
        *id = queue_counter;

        if ( new_sem == SEM_FAILED) {
            if ( errno == EINVAL || errno == ENOMEM || errno == EMFILE ) {
                return NULL;
            }
        }

        queue_counter++; // overflow is acceptable

        if ( queue_counter == initial_counter ) {
            // overflowed and came back around to the initial position
            // practical limit for max number of queues with the current name implementation
            return NULL;
        }
    }

    return new_sem;
}

void close_sem( size_t sem_id ) {
    char name[255] = { 0 };
    get_sem_name( name, sem_id );
    sem_unlink( name );
}


int add( struct dc_threaded_queue * queue, void * element );

void * take( struct dc_threaded_queue * queue );


struct dc_threaded_queue * dc_threaded_queue_init( size_t max_size ) {
    struct dc_threaded_queue * new_queue = ( struct dc_threaded_queue * ) malloc( sizeof( struct dc_threaded_queue ));

    if ( !new_queue ) {

        return NULL;
    }

    new_queue->consumer_sem = open_sem( max_size, &new_queue->consumer_sem_id );
    if ( !new_queue->consumer_sem ) {
        free( new_queue );
        return NULL;
    }

    new_queue->producer_sem = open_sem( 0, &new_queue->producer_sem_id );
    if ( !new_queue->producer_sem ) {
        close_sem( new_queue->consumer_sem_id );
        free( new_queue );
        return NULL;
    }

    new_queue->list = dlinked_create_list();
    if ( !new_queue->list ) {
        close_sem( new_queue->consumer_sem_id );
        close_sem( new_queue->producer_sem_id );
        free( new_queue );
        return NULL;
    }

    int mx_stat = pthread_mutex_init( &new_queue->list_mx, NULL);
    if ( mx_stat != 0 ) {
        close_sem( new_queue->consumer_sem_id );
        close_sem( new_queue->producer_sem_id );
        dlinked_free_list( &new_queue->list );
        free( new_queue );
        return NULL;
    }

    new_queue->add = add;
    new_queue->take = take;
    return new_queue;
}

void dc_threaded_queue_destroy( struct dc_threaded_queue ** queue ) {
    close_sem(( *queue )->consumer_sem_id );
    close_sem(( *queue )->producer_sem_id );
    dlinked_free_list( &( *queue )->list );
    free( *queue );
    *queue = NULL;
}

int add( struct dc_threaded_queue * queue, void * element ) {
    int stat = sem_wait( queue->consumer_sem );
    if ( stat != 0 ) {
        return DCTQ_ERR_SWAIT;
    }

    stat = pthread_mutex_lock( &queue->list_mx );

    if ( stat != 0 ) {
        return DCTQ_ERR_MXLK;
    }

    stat = dlinked_push( queue->list, element );
    if ( stat != SUCCESS ) {
        return stat;
    }

    stat = pthread_mutex_unlock( &queue->list_mx );
    if (stat != 0 ) {
        return DCTQ_ERR_MXULK;
    }

    stat = sem_post( queue->producer_sem );
    if (stat != 0 ) {
        return stat;
    }

    return SUCCESS;
}

void * take( struct dc_threaded_queue * queue ) {
    int stat = sem_wait( queue->producer_sem );
    if ( stat != 0 ) {
        return NULL;
    }

    stat = pthread_mutex_lock( &queue->list_mx );

    if ( stat != 0 ) {
        return NULL;
    }

    void * el = dlinked_pop_head( queue->list );
    if ( !el ) {
        return NULL;
    }

    pthread_mutex_unlock( &queue->list_mx );
    sem_post( queue->consumer_sem );

    return el;
}
