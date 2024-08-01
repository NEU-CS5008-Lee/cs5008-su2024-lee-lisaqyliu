//Qingyang Liu
//liu.qingyan@northeastern.edu
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t chopstick[5];//lock variable
// Mutex: at most one threat may own the lock. When thread A is holding the lock, no other thread can acquire the lock.
// Thread to be executed
void *philosopher(void *x)
{
    //Treat variable x as a pointer to an int and then extract the value into n
    int* a=(int*)x;
    int n=*a;
    
    /*-----Insert your code here----*/
    // Think
    printf("Philosopher %d is thinking.\n", n);
    sleep(1); // Simulate thinking

    // Pick up chopsticks in order
    if (n == 4) { // Last philosopher picks right first, then left
        pthread_mutex_lock(&chopstick[(n+1)%5]); // Right chopstick
        printf("Philosopher %d is eating using chopstick[%d] and chopstick[%d].\n", n, (n+1)%5, n);
        pthread_mutex_lock(&chopstick[n]);       // Left chopstick
    } else { // All other philosophers pick left first, then right
        pthread_mutex_lock(&chopstick[n]);       // Left chopstick
        pthread_mutex_lock(&chopstick[(n+1)%5]); // Right chopstick
        printf("Philosopher %d is eating using chopstick[%d] and chopstick[%d].\n", n, n, (n+1)%5);
    }

    // Eat
    sleep(1); // Simulate eating

    // Put down chopsticks
    pthread_mutex_unlock(&chopstick[n]);             // Left chopstick
    pthread_mutex_unlock(&chopstick[(n+1)%5]);       // Right chopstick

    printf("Philosopher %d finished eating.\n", n);
    return NULL; // Return from the thread after one cycle
    
}


/*------------ Main Program---------*/
int main()
{
    int i,val[5];
    pthread_t threads[5];
    //initializing the mutex (for chopsticks)
    for(i=0;i<5;i++){
        pthread_mutex_init(&chopstick[i],NULL);
    }   

    //create and run the thread
    for(i=0;i<5;i++){
        val[i]=i;
        pthread_create(&threads[i],NULL,(void *)philosopher,&val[i]);
    }
    
    //wait until all the threads are done
    for(i=0;i<5;i++){
        pthread_join(threads[i],NULL);
    }
    
    // Destroying the mutex
    for(i=0;i<5;i++){
        pthread_mutex_destroy(&chopstick[i]);
    }
    
    return 0;
}