#include "philo.h"

void print_status(t_philosopher *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->someone_died && !philo->data->all_satisfied)
        printf("%ld %d %s\n", 
            get_current_time() - philo->data->start_time,
            philo->id + 1, status);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    if (philo->id % 2)
        my_sleep(1);
    while (!philo->data->someone_died && !philo->data->all_satisfied)
    {
        thinking(philo);
        take_forks(philo);
        eating(philo);
        put_down_forks(philo);
        sleeping(philo);
    }
    return (NULL);
}