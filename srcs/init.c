/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hykang <hykang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:38:30 by hykang            #+#    #+#             */
/*   Updated: 2022/07/16 20:03:03 by hykang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_minilibx(t_game *game)
{
	int	w;
	int	h;

	w = game->width;
	h = game->height;
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, w * TILES, \
	h * TILES, "[so_long]");
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

void	get_map_col(t_game *game, char *line, int l)
{
	int		i;

	i = 0;
	game->map[l] = (char *)malloc(sizeof(char) * game->width);
	while (line[i])
	{
		if (line[i] == 'P')
		{
			game->position.x = i;
			game->position.y = l;
		}
		game->map[l][i] = line[i];
		i++;
	}
}

int	check_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
		{
			close_game_with_error(4);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_map(t_game *game, int fd)
{
	int		i;
	int		is_valid;
	char	*line;

	i = 0;
	is_valid = 1;
	game->map = (char **)malloc(sizeof(char *) * game->height);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		get_map_col(game, line, i);
		if (i + 1 == game->height)
			is_valid = check_last_line(line);
		if (!is_valid)
			close_game(game, 0);
		draw_map(game, line, i);
		free(line);
		i++;
	}
	ft_putstr_fd("--------------------\n", 1);
	ft_putstr_fd("    Game start !\n", 1);
	ft_putstr_fd("--------------------\n", 1);
}
