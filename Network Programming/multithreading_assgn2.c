#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

void *thread_fn_callback(void *th_id) {
    
    printf("%d\n", *(int*)th_id);
}
void moderator_thread(pthread_t *reducer_thread,
        int nthreads) {

    //pthread_attr_t **attr = calloc(nthreads, sizeof(pthread_attr_t));
    pthread_attr_t attr;
    int *_th_id = calloc(1, sizeof(int));
    void **th_res = calloc(nthreads, sizeof(int));
    pthread_attr_init(&attr);
    for(int th_id = nthreads; th_id > 0; th_id--) {
        *_th_id = th_id;
        pthread_attr_setdetachstate(&attr,
                PTHREAD_CREATE_JOINABLE);
        pthread_create(reducer_thread,
                &attr,
                thread_fn_callback,
                (void*)_th_id);
        pthread_join(*reducer_thread, &th_res[th_id]);
    }
    free(_th_id);
    free(th_res);
}

int main(int argc, char **argv) {

    pthread_t reducer_thread;
    if(argc < 2) {

        printf("Insufficient arguments supplied!\n");
        exit(0);
    } else if(argc > 3) {

        printf("Too many arguments!\n");
        exit(0);
    }
    moderator_thread(&reducer_thread, atoi(argv[1]));

    return 0;
}
