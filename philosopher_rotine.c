#include "philo.h"

// 考える
void thinking(t_philosopher *philo)
{
    print_status(philo, "is thinking");
}

// フォークを取る
int take_forks(t_philosopher *philo)
{
    int left_fork;
    int right_fork;

    if (philo->id % 2 == 0)
        usleep(100);
    // 左右のフォークの番号を計算
    if (philo->id == philo->data->num_philosophers - 1)
    {
        // 最後の哲学者は右→左の順でフォークを取る
        right_fork = 0;
        left_fork = philo->id;
    }
    else
    {
        // その他の哲学者は左→右の順でフォークを取る
        left_fork = philo->id;
        right_fork = (philo->id + 1) % philo->data->num_philosophers;
    }
    // 左のフォークを取る
    pthread_mutex_lock(&philo->data->forks[left_fork]);
    print_status(philo, "has taken a fork");

    // 右のフォークを取る
    // フォークのインデックスは哲学者のID+1になるが、最後の哲学者の場合は0になる
    pthread_mutex_lock(&philo->data->forks[right_fork]);
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
void put_down_forks(t_philosopher *philo)
{
    int left_fork = philo->id;
    int right_fork = (philo->id + 1) % philo->data->num_philosophers;

    // フォークを解放（順番は重要ではない）
    pthread_mutex_unlock(&philo->data->forks[left_fork]);
    pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

// 寝る
void sleeping(t_philosopher *philo)
{
    print_status(philo, "is sleeping");
    // 指定された時間だけ寝る
    usleep(philo->data->time_to_sleep * 1000);
}