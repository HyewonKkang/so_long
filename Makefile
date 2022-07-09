CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
NAME = so_long

SRCS = main.c draw.c init.c map.c player.c utils.c
OBJS = $(SRCS:.c=.o)

MLX_NAME = mlx
MLX_DIR = ./include/mlx
GNL_NAME = gnl
GNL_DIR = ./include/get_next_line

all: $(NAME)

$(NAME): $(SRCS)
	arch -x86_64 $(MAKE) -C $(MLX_DIR) all
	$(MAKE) -C $(GNL_DIR) all
	arch -x86_64 $(CC) $(CFLAGS) -L$(MLX_DIR) -l$(MLX_NAME) \
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
