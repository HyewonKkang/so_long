# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hykang <hykang@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 13:39:25 by hykang            #+#    #+#              #
#    Updated: 2022/07/13 14:07:08 by hykang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
NAME = so_long

SRCS = srcs/main.c srcs/draw.c srcs/init.c srcs/map.c srcs/player.c srcs/utils.c
OBJS = $(SRCS:.c=.o)

MLX_NAME = mlx
MLX_DIR = ./include/mlx
GNL_NAME = gnl
GNL_DIR = ./include/get_next_line

all: $(NAME)

$(NAME): $(SRCS)
	$(MAKE) -C $(MLX_DIR) all
	$(MAKE) -C $(GNL_DIR) all
	$(CC) $(CFLAGS) -L$(MLX_DIR) -l$(MLX_NAME) \
		-L$(GNL_DIR) -l$(GNL_NAME) \
		-framework OpenGL -framework AppKit $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@

clean:
	rm -f *.o
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	rm -f $(NAME) $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(GNL_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
