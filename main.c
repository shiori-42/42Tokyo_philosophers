#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    
    if (init_data(&data, argc, argv) != 0)
        return (1);
    if (init_forks(&data) != 0)
    {
        free_resources(&data);
        return (1);
    }
    if (init_philosophers(&data) != 0)
    {
        free_resources(&data);
        return (1);
    }
    if (start_simulation(&data) != 0)
    {
        free_resources(&data);
        return (1);
    }
    free_resources(&data);
    return (0);
}