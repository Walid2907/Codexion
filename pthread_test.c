#include "codexion.h"

pthread_mutex_t mutex;
void *test(void *mail)
{
    int *t = (int *)mail;
    for(int i=0; i<1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        (*t)++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main()
{
    pthread_mutex_init(&mutex, NULL);
    int mail = 0;
    pthread_t th[4];
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&th[i], NULL, test, &mail);
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_join(th[i], NULL);
    }
    printf("number %d", mail);
}