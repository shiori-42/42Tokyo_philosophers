#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_data   t_data;

typedef struct s_philosopher
{
    int             id;
    int             eat_count;
    bool            is_satisfied;
    long            last_meal_time;
    pthread_t       thread;
    t_data          *data;
}   t_philosopher;

typedef struct s_data
{
    int             num_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    long            start_time;
    bool            someone_died;
    bool            all_satisfied;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    t_philosopher   *philosophers;
}   t_data;

// main.c
int     main(int argc, char **argv);

// init.c
int     init_data(t_data *data, int argc, char **argv);
int     init_forks(t_data *data);
int     init_philosophers(t_data *data);
int     start_simulation(t_data *data);

// philosophers.c
void    *philosopher_routine(void *arg);
void    print_status(t_philosopher *philo, char *status);

// actions.c
void    thinking(t_philosopher *philo);
int     take_forks(t_philosopher *philo);
void    eating(t_philosopher *philo);
void    put_down_forks(t_philosopher *philo);
void    sleeping(t_philosopher *philo);

// monitor.c
void    *monitor_routine(void *arg);
int     check_death(t_philosopher *philo);
int     check_all_ate(t_data *data);

// utils.c
long    get_current_time(void);
void    my_sleep(long ms);
void    free_resources(t_data *data);

#endif