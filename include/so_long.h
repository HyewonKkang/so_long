/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hykang <hykang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:14:04 by hykang            #+#    #+#             */
/*   Updated: 2022/07/16 20:12:59 by hykang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "./get_next_line/get_next_line.h"
# include "./mlx/mlx.h"

# define TILES 64
# define X_EVENT_KEYPRESS 2
# define X_EVENT_EXIT 17

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

typedef struct s_param
{
	int		x;
	int		y;
	int		tile_x;
	int		tile_y;
	void	*img_ptr;

}	t_param;

typedef struct s_map
{
	int	wall;
	int	player;
	int	collectible;
	int	exit;
}		t_map;

typedef struct s_img
{
	void	*img_ptr;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	int			collected;
	int			move;
	t_param		position;
	t_img		img;
	t_map		map_textures;
	char		**map;
}	t_game;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

int		check_valid_move(t_game *game, int x, int y, int keycode);
int		check_player_move(int keycode, t_game *game);
void	passing_exit(t_game *game, int prev_x, int prev_y);
void	draw_updated_player(t_game *game, int prev_x, int prev_y);
int		press_key(int keycode, t_game *game);

void	init_minilibx(t_game *game);
void	init_param(t_game *game);
void	get_map_col(t_game *game, char *line, int l);
void	init_map(t_game *game, int fd);
int		check_last_line(char *line);

void	set_map_value(t_game *game, char component);
void	check_map_line(t_game *game, char *line, int check_wall);
void	check_map_components(t_game *game);
void	get_map(t_game *game, int fd);

void	draw_pixels_of_tile(t_game *game, char texture);
void	draw_map(t_game *game, char *line, int l);

int		close_game(t_game *game, int type);
int		close_game_with_error(int type);
void	print_move(char c);

#endif
