/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:35:39 by kdrazek           #+#    #+#             */
/*   Updated: 2025/05/20 15:37:18 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	if (!game->map)
		return ;
	game->collectible = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			textures(game, y, x);
			x++;
		}
		y++;
	}
	if (game->collectible < 1 && game->moves == 0)
	{
		write(2, "Error\nNo collectible", 20);
		cleanall(game);
	}
}

void	textures(t_game *game, int y, int x)
{
	void	*texture;

	texture = NULL;
	if (game->map[y][x] == '1')
		texture = game->textures.wall;
	else if (game->map[y][x] == '0')
		texture = game->textures.floor;
	else if (game->map[y][x] == 'P')
		texture = game->textures.player;
	else if (game->map[y][x] == 'E')
		texture = game->textures.exit;
	else if (game->map[y][x] == 'C')
	{
		texture = game->textures.collectible;
		game->collectible++;
	}
	mlx_put_image_to_window(game->mlx, game->win, texture, x * 64, y * 64);
}

void	load_textures(t_game *game)
{
	int	w;
	int	h;

	game->textures.wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&w, &h);
	game->textures.floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &w, &h);
	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &w, &h);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&w, &h);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &w, &h);
	if (!game->textures.wall || !game->textures.floor || !game->textures.player
		|| !game->textures.exit || !game->textures.collectible)
	{
		write(2, "Error\nOne of the textures do not loading", 41);
		cleanall(game);
	}
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	square(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	game->copy = ft_split(game->string_map, '\n');
	k = ft_strlen(game->copy[0]);
	while (game->copy[i])
	{
		j = ft_strlen(game->copy[i]);
		if (j != k)
		{
			write(2, "Error\nMap is't square or rectangular", 36);
			cleanall(game);
		}
		i++;
	}
	borders(game);
	is_map(game);
}
