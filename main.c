#include "include/so_long.h"

int close_game(t_game *game)
{
	int i;

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
	exit(0);

}

int	close_game_with_error(int type)
{
	if (type == 0)
		ft_putstr_fd("Error\n[Invalid Map]\n", 1);
	exit(0);
}

int main(int argc, char *argv[])
{
	t_game game;
	int fd;

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
