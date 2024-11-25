#include "philo.h"

void *print_message(void *thread_id) {
    int id = *(int *)thread_id;
    printf("Thread %d is running\n", id);
    sleep(20);
    pthread_exit(NULL);
}

int main() {
    t_data data;
    int num_philosophers = 5;
    data.num_philosophers = num_philosophers;
    data.time_to_eat = 200;  // 200ミリ秒
    data.time_to_sleep = 300; // 300ミリ秒

    // フォークを初期化
    init_forks(&data, num_philosophers);

    // 哲学者構造体とスレッドの配列を作成
    t_philosopher philosophers[num_philosophers];
    pthread_t threads[num_philosophers];

    // スレッドを作成して哲学者のルーチンを実行
    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i].id = i;
        philosophers[i].last_meal_time = get_current_time();
        philosophers[i].data = &data;  // 各哲学者にデータ構造体へのポインタを渡す
        pthread_create(&threads[i], NULL, philosopher_rotine, &philosophers[i]);
    }

    // スレッドが終了するのを待機（実際は無限ループなのでCtrl+Cで終了）
    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(threads[i], NULL);
    }

    // フォークを解放
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&data.forks[i]);
    }
    free(data.forks);

    return 0;
}



// int main() {
//     pthread_t threads[2];
//     int thread_ids[2] = {0, 1};

//     for (int i = 0; i < 2; i++) {
//         pthread_create(&threads[i], NULL, print_message, (void *)&thread_ids[i]);
//     }

//     for (int i = 0; i < 2; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     return 0;
// }
