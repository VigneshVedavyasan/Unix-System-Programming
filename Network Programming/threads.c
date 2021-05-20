#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

static void *thread_fn_call_back(void *arg) {

    char *input = (char*)arg;
    int a = 0;
    while(a < 10) {
        printf("Input string : %s\n", input);
        sleep(1);
        if(a == 4) {
            pthread_exit(0);
        }
        a++;
    }
    return 0;
}

void thread1_create() {

    pthread_t pthread1;
    static char *thread1_input = "I am thread# 1";

    int rc = pthread_create(&pthread1, NULL, thread_fn_call_back, (void*)thread1_input);

    if(rc != 0) {
        printf("Error occurred, thread couldn't be created, error code %d;", rc);
        exit(0);
    }
}

int main(int argc, char *argv[]) {

    thread1_create();
    printf("Main thread\n");
    pthread_exit(0);
    return 0;
}
