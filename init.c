#include "philo.h"
#include <limits.h>

static int parse_arg(const char *arg)
{
    long num;
    int i;

    i = 0;
    num = 0;
    if (arg[0] == '-')
        return (-1);
    while (arg[i])
    {
        if (arg[i] < '0' || arg[i] > '9')
            return (-1);
        num = num * 10 + (arg[i] - '0');
        if (num > INT_MAX)
            return (-1);
        i++;
    }
    return ((int)num);
}

int init_data(t_data *data, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    data->num_philosophers = parse_arg(argv[1]);
    data->time_to_die = parse_arg(argv[2]);
    data->time_to_eat = parse_arg(argv[3]);
    data->time_to_sleep = parse_arg(argv[4]);
    data->must_eat_count = (argc == 6) ? parse_arg(argv[5]) : -1;

    if (data->num_philosophers <= 0 || data->time_to_die < 0 ||
        data->time_to_eat < 0 || data->time_to_sleep < 0 ||
        (argc == 6 && data->must_eat_count <= 0))
    {
        printf("Error: invalid arguments\n");
        return (1);
    }
    data->someone_died = false;
    data->all_satisfied = false;
    data->philosophers = NULL;
    data->forks = NULL;
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
        return (1);
    return (0);
}

int init_forks(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    if (!data->forks)
        return (1);
    i = -1;
    while (++i < data->num_philosophers)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i]);
            free(data->forks);
            data->forks = NULL;
            return (1);
        }
    }
    return (0);
}

int init_philosophers(t_data *data)
{
    int i;

    data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
    if (!data->philosophers)
        return (1);
    i = -1;
    while (++i < data->num_philosophers)
    {
        data->philosophers[i].id = i;
        data->philosophers[i].eat_count = 0;
        data->philosophers[i].is_satisfied = false;
        data->philosophers[i].data = data;
    }
    return (0);
}

int start_simulation(t_data *data)
{
    int i;
    pthread_t monitor;

    data->start_time = get_current_time();
    i = -1;
    while (++i < data->num_philosophers)
    {
        data->philosophers[i].last_meal_time = get_current_time();
        if (pthread_create(&data->philosophers[i].thread, NULL,
            philosopher_routine, &data->philosophers[i]) != 0)
            return (1);
    }
    if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
        return (1);
    i = -1;
    while (++i < data->num_philosophers)
        pthread_join(data->philosophers[i].thread, NULL);
    pthread_join(monitor, NULL);
    return (0);
}