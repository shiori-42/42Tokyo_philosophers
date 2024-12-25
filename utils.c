#include "philo.h"

long get_current_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void my_sleep(long ms)
{
    long start;
    long end;
    
    start = get_current_time();
    end = start + ms;
    while (get_current_time() < end)
        usleep(100);
}

void free_resources(t_data *data)
{
    int i;

    if (data->forks)
    {
        i = -1;
        while (++i < data->num_philosophers)
            pthread_mutex_destroy(&data->forks[i]);
        free(data->forks);
    }
    pthread_mutex_destroy(&data->print_mutex);
    if (data->philosophers)
        free(data->philosophers);
}