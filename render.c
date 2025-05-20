/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:32:08 by kdrazek           #+#    #+#             */
/*   Updated: 2025/05/19 18:46:41 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_game *game, int y, int x)
{
	if (game->copy[y][x] == 'F'
		|| game->copy[y][x] == 'E'
		|| game->copy[y][x] == '1')
		return ;
	game->copy[y][x] = 'F';
	flood_fill(game, y - 1, x);
	flood_fill(game, y + 1, x);
	flood_fill(game, y, x - 1);
	flood_fill(game, y, x + 1);
}

void	map_valid(t_game *game, int i, int j, int k)
{
	while (game->copy[i])
	{
		j = 0;
		while (game->copy[i][j])
		{
			if (game->copy[i][j] == 'C')
				k++;
			if (game->copy[i][j] == 'E')
			{
				if ((j + 1 < game->map_width && game->copy[i][j + 1] == 'F')
					|| (j - 1 >= 0 && game->copy[i][j - 1] == 'F') || (i
						+ 1 < game->map_height && game->copy[i + 1][j] == 'F')
					|| (i - 1 >= 0 && game->copy[i - 1][j] == 'F'))
					game->exit_reachable = 1;
			}
			j++;
		}
		i++;
	}
	if (k > 0 || game->exit_reachable == 0)
	{
		write(2, "Error\nImpossable map", 20);
		cleanall(game);
	}
}

void	borders(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (game->copy[0][j])
		if (game->copy[0][j++] != '1')
			k++;
	while (game->copy[i])
		if (game->copy[i][0] != '1' || game->copy[i++][j - 1] != '1')
			k++;
	j = 0;
	while (game->copy[i - 1][j])
		if (game->copy[i - 1][j++] != '1')
			k++;
	if (k != 0)
	{
		write(2, "Error\nBorders are not 1", 23);
		cleanall(game);
	}
}

void	is_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->copy[i])
	{
		j = 0;
		while (game->copy[i][j])
		{
			if (game->copy[i][j] != '1' && game->copy[i][j] != '0'
				&& game->copy[i][j] != 'C' && game->copy[i][j] != 'P'
				&& game->copy[i][j] != 'E')
			{
				write(2, "Error\nMap is't only 1, 0, P, C or E", 35);
				cleanall(game);
			}
			j++;
		}
		i++;
	}
	map_exit_player(game);
}

void	map_exit_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->copy[i])
	{
		j = 0;
		while (game->copy[i][j])
		{
			if (game->copy[i][j] == 'P')
				game->player++;
			if (game->copy[i][j] == 'E')
				game->exit++;
			j++;
		}
		i++;
	}
	if (game->exit != 1 || game->player != 1)
	{
		write(2, "Error\nMap don't have one exit or one position player", 29);
		cleanall(game);
	}
	find_player(game);
	flood_fill(game, game->player_y, game->player_x);
	map_valid(game, 0, 0, 0);
}
