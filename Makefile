# Makefile for Minishell

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes
SRCS = 
OBJS = $(SRCS:.c=.o)
READLINE = -lreadline
RM = rm -f  # 削除コマンドを変数に定義

.PHONY: all clean fclean re

# デフォルトターゲット
all: $(NAME)

# バイナリ生成ルール
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# ソースファイルからオブジェクトファイル生成
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# クリーンアップ
clean:
	$(RM) $(OBJS)

# 全ての生成物を削除
fclean: clean
	$(RM) $(NAME)

# 再ビルド
re: fclean all