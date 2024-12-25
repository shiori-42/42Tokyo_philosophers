// error.c
#include "philo.h"

// エラーメッセージを表示して終了
void error_exit(char *message)
{
    printf("Error: %s\n", message);
    exit(1);
}

// リソースを解放する関数
void cleanup_resources(t_data *data)
{
    int i;

    pthread_mutex_destroy(&data->print_mutex);

    if (data->forks)
    {
        i = 0;
        while(i < data->num_philosophers)
        {
            pthread_mutex_destroy(&data->forks[i]);
             i++;
        }
        free(data->forks);
    }
}

