# include"codexion.h"


void *routine(void *data)
{
    t_coder *coder;

    coder = (t_coder *)data;


    return(NULL);
}

int    simulation_start(t_data *data)
{
    int i;

    i = 0;
    while(i < data->args->number_of_coders)
    {
        if(safe_pthread(CREATE, &data->coders[i].thread_id, routine, &data->coders[i]) == FAILED)
            return FAILED;
    }
}