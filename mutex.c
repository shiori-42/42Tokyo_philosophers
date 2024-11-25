#include "philo.h"

/*
メモリ上に num_philosophers 個のミューテックス（鍵）が確保され、それぞれ初期化されています。
各ミューテックスは、後で哲学者が「このフォークを使えるかどうか」を管理するために利用されます。
*/

// フォークを初期化する関数
void init_forks(t_data *data)
{
    // フォーク（ミューテックス）の配列をメモリ確保
    data->forks=malloc(sizeof(pthread_mutex_t)*data->num_philosophers);
    //data.forks: [フォーク1, フォーク2, フォーク3, フォーク4, フォーク5]
    if (!data->forks)
        return ;  // エラー処理は後で追加
    
    //各フォークを「ロックやアンロックができる状態」に初期化している
    for (int i = 0; i < data->num_philosophers; i++)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return ;  // エラー処理は後で追加
    }
}
