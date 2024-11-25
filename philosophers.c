#include "philo.h"

void *philosopher_rotine(void *argv)
{
    // 哲学者のデータを受け取る（argを哲学者構造体に変換する）
    t_philosopher *philosopher = (t_philosopher *)argv;
     t_data *data = philosopher->data;  // データ構造体へのポインタを取得

    // 無限ループで哲学者の行動を繰り返す
    while (1)
    {
        // 哲学者が考え始める
        printf("Philosopher %d is thinking\n", philosopher->id);

        // 左のフォークを掴む（ロックする）
        pthread_mutex_lock(&data->forks[philosopher->id]);

        // 右のフォークを掴む（ロックする）
        // フォークのインデックスは哲学者のID+1になるが、最後の哲学者の場合は0になる
        pthread_mutex_lock(&data->forks[(philosopher->id + 1) % data->num_philosophers]);

        // 今の時間を記録して最後に食べた時刻を更新
        philosopher->last_meal_time = get_current_time();
    
        // 哲学者が食べている
        printf("Philosopher %d is eating\n", philosopher->id);

        // 食事時間だけプログラムを止める（食べるのに）かかる時間を待つ
        usleep(data->time_to_eat * 1000);

        // 左のフォークを戻す（ロック解除する）
        pthread_mutex_unlock(&data->forks[philosopher->id]);

        // 右のフォークを戻す（ロック解除する）
        pthread_mutex_unlock(&data->forks[(philosopher->id + 1) % data->num_philosophers]);

        // 哲学者が眠り始める
        printf("Philosopher %d is sleeping\n", philosopher->id);

        // 眠る時間だけプログラムを止める（眠るのに）かかる時間を待つ
        usleep(data->time_to_sleep * 1000);

    }
    return (NULL);
}