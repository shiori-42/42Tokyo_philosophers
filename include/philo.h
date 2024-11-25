#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

//一人一人の哲学者の情報を持つ構造体
typedef struct s_philosopher{
    int id; // 哲学者のID
    long last_meal_time; // 最後に食事をした時間、哲学者が飢え死にするかどうかをチェックするために使用
    struct s_data *data;  // データ構造体へのポインタを追加
} t_philosopher;

//哲学者全体の情報や共有データ持つ構造体
typedef struct s_data{
    int num_philosophers; // 哲学者の人数
    int time_to_die; // もし哲学者が最後の食事や趣味レーションの開始からtime_to_die秒以内に食事をしなかった場合、死亡する
    int time_to_eat; // 食事にかかる時間（ミリ秒）、2本のフォークを持つ必要がある
    int time_to_sleep; //　睡眠にかかる時間（ミリ秒
    pthread_mutex_t *forks; // フォーク（ミューテックスの配列）
}t_data;

void init_forks(t_data *data, int num_philosophers);
long get_current_time();
void *philosopher_rotine(void *argv);


#endif