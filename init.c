#include "include/so_long.h"

void init_minilibx(t_game *game)
{
	int w;
	int	h;

	w = game->width;
	h = game->height;
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, w * TILES, h * TILES, "[so_long]");
}

void pos_init(t_param *param)
{
	param->x = 0;
	param->y = 0;
}

void	init_param(t_game *game)
{
	game->width = 0;
	game->height = 0;
	game->map_textures.wall = 0;
	game->map_textures.player = 0;
	game->map_textures.collectible = 0;
	game->map_textures.exit = 0;
	game->collected = 0;
	game->move = 0;
	game->map = NULL;
	game->position.x = 0;
	game->position.y = 0;
}


void get_map_col(t_game *game, char *line, int l)
{
	int	i;
	char *arr;

	i = 0;
	arr = (char *)malloc(sizeof(char) * game->width);
	while (line[i])
	{
		if (line[i] == 'P')
		{
			game->position.x = i;
			game->position.y = l;
		}
		arr[i] = line[i];
		i++;
	}
	game->map[l] = arr;

}

void	init_map(t_game *game, int fd)
{
	int i;
	char *line;

	i = 0;
	game->map = (char **)malloc(sizeof(char *) * game->height);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		get_map_col(game, line, i);
		draw_map(game, line, i);
		free(line);
		i++;
	}
	ft_putstr_fd("--------------------\n", 1);
	ft_putstr_fd("    Game start !\n", 1);
	ft_putstr_fd("--------------------\n", 1);
}
