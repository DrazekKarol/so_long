/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:28 by kdrazek           #+#    #+#             */
/*   Updated: 2025/05/20 15:38:12 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_y = game->player_y;
	new_x = game->player_x;
	if (keycode == 119)
		new_y--;
	else if (keycode == 115)
		new_y++;
	else if (keycode == 97)
		new_x--;
	else if (keycode == 100)
		new_x++;
	else if (keycode == 65307)
		cleanall(game);
	if (new_x >= 0 && new_x < game->map_width && new_y >= 0
		&& new_y < game->map_height && game->map[new_y][new_x] == 'C')
		game->collectible--;
	next_move(new_x, new_y, game);
	if (new_x >= 0 && new_x < game->map_width && new_y >= 0
		&& new_y < game->map_height && game->map[new_y][new_x] == 'E'
		&& game->collectible == 0)
		when_exit(game, new_x, new_y);
	return (0);
}

void	next_move(int new_x, int new_y, t_game *game)
{
	if (new_x >= 0 && new_x < game->map_width && new_y >= 0
		&& new_y < game->map_height && game->map[new_y][new_x] != '1'
		&& game->map[new_y][new_x] != 'E')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->map[new_y][new_x] = 'P';
		game->player_x = new_x;
		game->player_y = new_y;
		game->moves++;
		printf("Moves counter: %d\n", game->moves);
		draw_map(game);
	}
}

int	close_window(t_game *game)
{
	cleanall(game);
	return (0);
}

void	destroy_textures(t_game *game)
{
	if (game->textures.collectible)
		mlx_destroy_image(game->mlx, game->textures.collectible);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx, game->textures.exit);
	if (game->textures.floor)
		mlx_destroy_image(game->mlx, game->textures.floor);
	if (game->textures.player)
		mlx_destroy_image(game->mlx, game->textures.player);
	if (game->textures.wall)
		mlx_destroy_image(game->mlx, game->textures.wall);
}

void	cleanall(t_game *game)
{
	if (game->string_map)
		free(game->string_map);
	free_split(game->map);
	free_split(game->copy);
	if (game->mlx)
	{
		destroy_textures(game);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	exit(1);
}
