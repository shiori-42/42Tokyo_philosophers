#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h> 
#include <string.h> //ft_strcmp実装する

// 哲学者の状態を表す列挙型
typedef enum e_state {
    THINKING,   // 考え中
    EATING,     // 食事中
    SLEEPING,   // 睡眠中
    DIED        // 死亡
} t_state;

//共有データ持つ構造体
typedef struct s_data{
    int num_philosophers; // 哲学者の人数
    int time_to_die; // もし哲学者が最後の食事からtime_to_die秒以内に食事をしなかった場合、死亡する
    int time_to_eat; // 食事にかかる時間（ミリ秒）、2本のフォークを持つ必要がある
    int time_to_sleep; //　睡眠時間（ミリ秒）
    long start_time; // プログラム開始時刻
    pthread_mutex_t *forks; // フォーク（ミューテックスの配列）
}t_data;

//各哲学者の情報を持つ構造体
typedef struct s_philosopher{
    int id; // 哲学者の番号（0からスタート）
    t_state state; // 現在の状態
    long last_meal_time; // 最後に食事した時間、哲学者が飢え死にするかどうかをチェックするために使用
    pthread_t thread; // スレッドを識別するための型、各哲学者は別々のスレッドで動作するため、それぞれにpthread_tが必要
    struct s_data *data;  // 共有データへのポインタ
} t_philosopher;


void init_forks(t_data *data);
long get_current_time();
void *philosopher_rotine(void *argv);
void print_status(t_philosopher *philo, char *status);
void thinking(t_philosopher *philo);
int take_forks(t_philosopher *philo);
void eating(t_philosopher *philo);
void put_down_forks(t_philosopher *philo);
void sleeping(t_philosopher *philo);

#endif