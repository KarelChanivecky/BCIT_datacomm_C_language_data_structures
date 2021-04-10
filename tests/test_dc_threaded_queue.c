/**
* karel on 2021-04-10.
*/

#include "../lib/dc_threaded_queue.h"
#include "unistd.h"
#include "stdio.h"

typedef struct test_case_t {
    struct dc_threaded_queue * q;
    int consumer_wait;
    int producer_wait;
} test_case_t;

void * producer_thread(void * v_args) {
    test_case_t * args = (test_case_t *) v_args;
    for (unsigned long i = 1; i < 11; i++) {
        sleep(args->producer_wait);
        args->q->add(args->q, (void * ) i);
        printf("produced: %zu\n", i);
    }

    return NULL;
}

void * consumer_thread(void * v_args) {
    test_case_t * args = (test_case_t *) v_args;
    for (int i = 1; i < 11; i++) {
        sleep(args->consumer_wait);
        void * el = args->q->take(args->q);
        printf("consumed: %zu\n", (unsigned long )el);
    }
    sleep(args->consumer_wait);
    return NULL;
}

void run_test_case(test_case_t * test_case) {
    pthread_t p_thread;
    pthread_t c_thread;
    pthread_create( &p_thread, NULL, producer_thread, test_case);
    pthread_create( &c_thread, NULL, consumer_thread, test_case);
    pthread_join(p_thread, NULL);
    pthread_join(c_thread, NULL);
}

void test_fast_consumer_fast_producer() {
    puts("testing fast consumer fast producer");
    test_case_t test_case;
    test_case.q = dc_threaded_queue_init(1);
    test_case.consumer_wait = 0;
    test_case.producer_wait = 0;
    run_test_case(&test_case);
}

void test_fast_consumer_slow_producer() {
    puts("testing fast consumer slow producer");
    test_case_t test_case;
    test_case.q = dc_threaded_queue_init(1);
    test_case.consumer_wait = 0;
    test_case.producer_wait = 1;
    run_test_case(&test_case);
}

void test_slow_consumer_fast_producer() {
    puts("testing slow consumer fast producer");
    test_case_t test_case;
    test_case.q = dc_threaded_queue_init(1);
    test_case.consumer_wait = 1;
    test_case.producer_wait = 0;
    run_test_case(&test_case);
}


int main() {
    test_fast_consumer_fast_producer();
    test_fast_consumer_slow_producer();
    test_slow_consumer_fast_producer();
    return 0;
}