#include "philo.h"

void thinking(t_philosopher *philo)
{
    print_status(philo, "is thinking");
}

int take_forks(t_philosopher *philo)
{
    if (philo->data->num_philosophers == 1)
    {
        pthread_mutex_lock(&philo->data->forks[0]);
        print_status(philo, "has taken a fork");
        pthread_mutex_unlock(&philo->data->forks[0]);
        while (!philo->data->someone_died)
            my_sleep(1);
        return (1);
    }

    pthread_mutex_lock(&philo->data->forks[philo->id]);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % 
        philo->data->num_philosophers]);
    print_status(philo, "has taken a fork");
    return (0);
}

void eating(t_philosopher *philo)
{
    print_status(philo, "is eating");
    philo->last_meal_time = get_current_time();
    my_sleep(philo->data->time_to_eat);
    philo->eat_count++;
    if (philo->data->must_eat_count > 0 && 
        philo->eat_count >= philo->data->must_eat_count)
        philo->is_satisfied = true;
}

void put_down_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(&philo->data->forks[philo->id]);
    pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % 
        philo->data->num_philosophers]);
}

void sleeping(t_philosopher *philo)
{
    print_status(philo, "is sleeping");
    my_sleep(philo->data->time_to_sleep);
}