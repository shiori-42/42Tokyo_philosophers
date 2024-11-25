#include "philo.h"

// 状態を表示する関数
void print_status(t_philosopher *philo, char *status)
{
    // 現在時刻を取得
    long current_time = get_current_time() - philo->data->start_time;

    // 状態を更新（これが抜けていました）
    if (strcmp(status, "is thinking") == 0)
        philo->state = THINKING;
    else if (strcmp(status, "is eating") == 0)
        philo->state = EATING;
    else if (strcmp(status, "is sleeping") == 0)
        philo->state = SLEEPING;

    // ステータスを表示
    printf("%ld %d %s\n", current_time, philo->id + 1, status);
}

// 哲学者の行動ルーチン（スレッドとして実行される
void *philosopher_rotine(void *argv)
{
    // 哲学者のデータを受け取る（argを哲学者構造体に変換する）
    t_philosopher *philo = (t_philosopher *)argv;

    // 無限ループで哲学者の行動を繰り返す
    while (1)
    {
        thinking(philo);        // 考える
        take_forks(philo);      // フォークを取る
        eating(philo);          // 食べる
        put_down_forks(philo);   // フォークを置く
        sleeping(philo);        // 寝る
    }
    return (NULL);

}