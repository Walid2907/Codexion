# include "codexion.h"


void *test(void *coder_i)
{
    t_coder *coder = coder_i;
    printf("Coder ID: %d\n", coder->coder_id);
    printf("Right hand: %d\n", coder->right_hand);
    printf("Left hand: %d\n", coder->left_hand);
    sleep(5);
    return (NULL);
}

int main()
{
    printf("start:\n");
    pthread_t *ar = malloc(sizeof(pthread_t) * 10);
    t_coder *coder = malloc(sizeof(t_coder) * 10);
    for(int i=0;i<10;i++)
    {
        coder[i].coder_id = i + 1;
        coder[i].left_hand = (i + 2) % 10;
        coder[i].right_hand = i + 1;
        coder[i].status = 0;
        if(pthread_create(&ar[i], NULL, test, &coder[i]) != 0)
            printf("ERROR: thread creation ERROR"); // this is to protect the function from failing while an error ocured when creating a thread
        sleep(5);

    }
    for(int i=0;i<10;i++)
    {
        if(pthread_join(ar[i], NULL) != 0)
            printf("ERROR: thread joining ERROR");  // this is to protect the function from failing while an error ocured when joining a thread
    }

    printf("end");
}