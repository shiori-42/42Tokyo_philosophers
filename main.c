#include "philo.h"

//一人一人の哲学者の情報を持つ構造体
typedef struct s_philosopher{
    pthread_t *threads; // スレッドを管理するためのポインタ
    long last_meal_time; // 最後に食事をした時間、哲学者が飢え死にするかどうかをチェックするために使用
} t_philosopher;

//哲学者全体の情報や共有データ持つ構造体
typedef struct s_data{
    int num_philosophers; // 哲学者の数とフォークの数
    int time_to_die; // もし哲学者が最後の食事や趣味レーションの開始からtime_to_die秒以内に食事をしなかった場合、死亡する
    int tim_to_eat; // 哲学者が食事をするのに必要な時間、2本のフォークを持つ必要がある
    int time_to_sleep; // 哲学者が睡眠に費やす時間
    pthread_mutex_t *forks; // フォーク（ミューテックスの配列）
}t_data

void *print_message(void *thread_id) {
    int id = *(int *)thread_id;
    printf("Thread %d is running\n", id);
    sleep(20);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int thread_ids[2] = {0, 1};

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, print_message, (void *)&thread_ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
