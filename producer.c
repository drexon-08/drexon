#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdint.h>
#include <time.h>

#define BUFF 10

sem_t full, empty, mutex;
int item, in = 0, out = 0;
int buffer[BUFF];

/* Producer Function */
void *producer(void *arg)
{
    int pno = (int)(intptr_t)arg;
    int item = rand() % 10;

    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[in] = item;

    printf("\nProducer P[%d] produced item = %d",
           pno, item);

    in = (in + 1) % BUFF;

    sem_post(&mutex);
    sem_post(&full);

    pthread_exit(NULL);
}

/* Consumer Function */
void *consumer(void *arg)
{
    int cno = (int)(intptr_t)arg;

    sem_wait(&full);
    sem_wait(&mutex);

    item = buffer[out];

    printf("\nConsumer C[%d] consumes item = %d",
           cno, item);

    out = (out + 1) % BUFF;

    sem_post(&mutex);
    sem_post(&empty);

    pthread_exit(NULL);
}

/* Main Function */
int main(void)
{
    pthread_t pro[20], con[20];
    int i, np, nc;

    srand(time(NULL));

    printf("\nEnter the number of producers (max 20): ");
    scanf("%d", &np);

    printf("Enter the number of consumers (max 20): ");
    scanf("%d", &nc);

    if (np < 1 || np > 20 || nc < 1 || nc > 20)
    {
        printf("Invalid number of producers or consumers.\n");
        return 1;
    }

    /* Initialize Semaphores */
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFF);
    sem_init(&mutex, 0, 1);

    /* Create Producer Threads */
    for (i = 0; i < np; i++)
    {
        pthread_create(&pro[i], NULL,
                       producer,
                       (void *)(intptr_t)i);
    }

    /* Wait for Producers */
    for (i = 0; i < np; i++)
    {
        pthread_join(pro[i], NULL);
    }

    /* Create Consumer Threads */
    for (i = 0; i < nc; i++)
    {
        pthread_create(&con[i], NULL,
                       consumer,
                       (void *)(intptr_t)i);
    }

    /* Wait for Consumers */
    for (i = 0; i < nc; i++)
    {
        pthread_join(con[i], NULL);
    }

    /* Destroy Semaphores */
    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);

    printf("\n\nProgram completed successfully.\n");

    return 0;
}
