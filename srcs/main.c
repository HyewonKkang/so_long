/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hykang <hykang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:38:36 by hykang            #+#    #+#             */
/*   Updated: 2022/07/13 15:06:31 by hykang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	close_game(t_game *game, int type)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free(game->mlx_ptr);
	if (type)
	{
		ft_putstr_fd("--------------------\n", 1);
		ft_putstr_fd(" The game is over !\n", 1);
		ft_putstr_fd("--------------------\n", 1);
	}
	exit(0);
}

int	close_game_with_error(int type)
{
	ft_putstr_fd("[Error]\n", 1);
	if (type == 0)
	{
		ft_putstr_fd("- The map must be composed of only ", 1);
		ft_putstr_fd("5 possible characters(0, 1, C, E, P) !\n", 1);
	}
	else if (type == 1)
		ft_putstr_fd("- There must be only one player !\n", 1);
	else if (type == 2)
		ft_putstr_fd("- There must be only one exit !\n", 1);
	else if (type == 3)
		ft_putstr_fd("- The map must be rectangular !\n", 1);
	else if (type == 4)
		ft_putstr_fd("- The map must be closed/surrounded by walls !\n", 1);
	else if (type == 5)
	{
		ft_putstr_fd("- Map must have at least one exit, one collectible, ", 1);
		ft_putstr_fd("and one starting position !\n", 1);
	}
	exit(0);
}

void	print_move(char c)
{
	ft_putstr_fd("Move : ", 1);
	ft_putnbr_fd(c, 1);
	ft_putchar_fd('\n', 1);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Type './so_long {map_name.ber}'\n", 1);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	init_param(&game);
	get_map(&game, fd);
	init_minilibx(&game);
	fd = open(argv[1], O_RDONLY);
	init_map(&game, fd);
	mlx_hook(game.win_ptr, X_EVENT_KEYPRESS, 0, &press_key, &game);
	mlx_hook(game.win_ptr, X_EVENT_EXIT, 0, &close_game, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
