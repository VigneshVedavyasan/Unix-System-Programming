#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>

pthread_t pthread2;
pthread_t pthread3;

void *
thread_fn_callback(void* arg) {

    int th_id = *(int*)arg;
    int rc = 0;
    int *result = calloc(1, sizeof(int));

    free(arg);

    while(rc != th_id) {

        printf("Thread %d doing some work\n", th_id);
        sleep(1);
        rc++;
    }
    *result = th_id * th_id;
    return (void*)result;
}

void
thread_create(pthread_t *pthread_handle, int th_id) {

    pthread_attr_t attr;
    int *_th_id = calloc(1, sizeof(int));
    *_th_id = th_id;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,
            PTHREAD_CREATE_JOINABLE);
    pthread_create(pthread_handle,
            &attr,
            thread_fn_callback,
            (void*)_th_id);
}

int main(int argc, char** argv) {

    void *thread_result2;
    void *thread_result3;
    thread_create(&pthread2, 2);
    thread_create(&pthread3, 10);

    printf("main fn block for thread 3 to join\n");
    pthread_join(pthread3, &thread_result3);
    if(thread_result3) {

        printf("Return result from thread 3 : %d\n",
                *(int*)thread_result3);
        free(thread_result3);
        thread_result3 = NULL;
    }
    printf("main fn block for thread 2 to join\n");
    pthread_join(pthread2, &thread_result2);
    if(thread_result2) {

        printf("Return result from thread 2 : %d\n",
                *(int*)thread_result2);
        free(thread_result2);
        thread_result2 = NULL;
    }
    return 0;
}
