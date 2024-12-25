#include "philo.h"

int check_death(t_philosopher *philo)
{
    long current_time;

    current_time = get_current_time();
    if (current_time - philo->last_meal_time >= philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        if (!philo->data->someone_died)
        {
            printf("%ld %d died\n", 
                current_time - philo->data->start_time, philo->id + 1);
            philo->data->someone_died = true;
        }
        pthread_mutex_unlock(&philo->data->print_mutex);
        return (1);
    }
    return (0);
}

int check_all_ate(t_data *data)
{
    int i;

    if (data->must_eat_count < 0)
        return (0);
    i = -1;
    while (++i < data->num_philosophers)
    {
        if (data->philosophers[i].eat_count < data->must_eat_count)
            return (0);
    }
    pthread_mutex_lock(&data->print_mutex);
    data->all_satisfied = true;
    pthread_mutex_unlock(&data->print_mutex);
    return (1);
}

void *monitor_routine(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    while (!data->someone_died && !data->all_satisfied)
    {
        i = -1;
        while (++i < data->num_philosophers)
        {
            if (check_death(&data->philosophers[i]))
                return (NULL);
        }
        if (check_all_ate(data))
            return (NULL);
        usleep(100);
    }
    return (NULL);
}