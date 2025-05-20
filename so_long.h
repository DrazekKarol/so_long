/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:21:44 by kdrazek           #+#    #+#             */
/*   Updated: 2025/05/20 14:55:34 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*player;
	void		*exit;
	void		*collectible;
}				t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*string_map;
	char		**map;
	char		**copy;
	int			map_width;
	int			map_height;
	t_textures	textures;
	int			player_x;
	int			player_y;
	int			collectible;
	int			exit;
	int			player;
	int			moves;
	int			exit_reachable;
}				t_game;

int				close_window(t_game *game);
int				handle_key(int keycode, t_game *game);
int				get_height_map(int fd, t_game *game);
int				main(int ac, char **av);
void			draw_map(t_game *game);
void			load_textures(t_game *game);
void			find_player(t_game *game);
void			when_exit(t_game *game, int x, int y);
void			destroy_textures(t_game *game);
void			flood_fill(t_game *game, int y, int x);
void			map_valid(t_game *game, int i, int j, int k);
void			borders(t_game *game);
void			textures(t_game *game, int y, int x);
void			next_move(int new_x, int new_y, t_game *game);
void			cleanall(t_game *game);
void			square(t_game *game);
void			structsetter(t_game *game);
void			map_checker(char *map_path, t_game *game);
int				path_valid(char *map_path);
void			is_map(t_game *game);
void			map_exit_player(t_game *game);
void			map_load(int fd, t_game *game, char *tmp, char *trimmed);
void			free_split(char **arr);
void			new_line(t_game *game, char *trimmed, char *joined);
#endif