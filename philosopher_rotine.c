#include "philo.h"

// 考える
void thinking(t_philosopher *philo)
{
    print_status(philo, "is thinking");
}

// フォークを取る
int take_forks(t_philosopher *philo)
{
    // 左のフォークを取る
    pthread_mutex_lock(&philo->data->forks[philo->id]);
    print_status(philo, "has taken a fork");

    // 右のフォークを取る
    // フォークのインデックスは哲学者のID+1になるが、最後の哲学者の場合は0になる
    pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->num_philosophers]);
    print_status(philo, "has taken a fork");

    return (0);
}

// 食べる
void eating(t_philosopher *philo)
{
    print_status(philo, "is eating");
    // 最後に食事をした時間を更新
    philo->last_meal_time = get_current_time();
    // 指定された時間だけ食べる
    usleep(philo->data->time_to_eat * 1000);
    // 食事回数をカウントアップ
    // philo->eat_count++;
}

// フォークを置く
void release_forks(t_philosopher *philo)
{
    // 左のフォークを戻す（ロック解除する）
    pthread_mutex_unlock(&philo->data->forks[philo->id]);
    // 右のフォークを戻す（ロック解除する）
    pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->num_philosophers]);
}

// 寝る
void sleeping(t_philosopher *philo)
{
    print_status(philo, "is sleeping");
    // 指定された時間だけ寝る
    usleep(philo->data->time_to_sleep * 1000);
}