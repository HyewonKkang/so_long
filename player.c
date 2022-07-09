#include "include/so_long.h"

int  check_valid_move(t_game *game, int x, int y)
{
	char cur;

	cur = game->map[y][x];
	if (cur == '1')
		return (0);
	else if (cur == 'C')
	{
		game->collected += 1;
		game->map[y][x] = '0';
	}
	else if (cur == 'E')
	{
		if (game->collected == game->map_textures.collectible)
			close_game(game);
		else
			ft_putstr_fd("There's still a collectible left!\n", 1);
	}
	return (1);
}

int check_player_move(int keycode, t_game *game)
{
	int x;
	int y;
	int flag;

	flag = 1;
	x = game->position.x;
	y = game->position.y;
	if (keycode == KEY_W)
		y--;
	else if (keycode == KEY_S)
		y++;
	else if (keycode == KEY_A)
		x--;
	else if (keycode == KEY_D)
		x++;
	else
		flag = 0;
	if (flag)
		flag = check_valid_move(game, x, y);
	if (flag)
	{
		if (game->map[game->position.y][game->position.x] \
		== 'E')
			flag = 2;
		game->position.x = x;
		game->position.y = y;
	}
	return (flag);
}

void	passing_exit(t_game *game, int prev_x, int prev_y)
{
	draw_pixels_of_tile(game, 'E');
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->img.img_ptr, prev_x, prev_y);
}

void	draw_updated_player(t_game *game, int prev_x, int prev_y)
{
	t_img	img;
	int		count_h;
	int		count_w;

	img = game->img;
	img.data = (int *)mlx_get_data_addr(game->position.img_ptr, &img.bpp, \
	&img.size_line, &img.endian);
	count_h = 0;
	while (count_h < TILES)
	{
		count_w = 0;
		while (count_w < TILES)
		{
			img.data[count_h * TILES + count_w] = 0x000000;
			count_w++;
		}
		count_h++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->position.img_ptr, prev_x, prev_y);
	draw_pixels_of_tile(game, 'P');
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->position.img_ptr, game->position.tile_x, game->position.tile_y);
}

int press_key(int keycode, t_game *game)
{
	int	prev_x;
	int	prev_y;
	int	flag;

	if (keycode == KEY_ESC)
		close_game(game);
	flag = check_player_move(keycode, game);
	if (flag)
	{
		prev_x = game->position.tile_x;
		prev_y = game->position.tile_y;
		if (keycode == KEY_W)
			game->position.tile_y -= TILES;
		else if (keycode == KEY_S)
			game->position.tile_y += TILES;
		else if (keycode == KEY_A)
			game->position.tile_x -= TILES;
		else if (keycode == KEY_D)
			game->position.tile_x += TILES;
		draw_updated_player(game, prev_x, prev_y);
		game->move += 1;
		if (flag == 2)
			passing_exit(game, prev_x, prev_y);
		ft_putstr_fd("Move : ", 1);
		ft_putnbr_fd(game->move, 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
