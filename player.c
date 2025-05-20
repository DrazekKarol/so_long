/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:43:08 by kdrazek           #+#    #+#             */
/*   Updated: 2025/05/20 14:55:35 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->moves = 0;
	while (game->copy[y])
	{
		x = 0;
		while (game->copy[y][x])
		{
			if (game->copy[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	when_exit(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->collectible == 0)
	{
		game->moves++;
		printf("Moves counter: %d\n", game->moves);
		printf("CONGRATULATION! YOU WIN!");
		cleanall(game);
	}
}

int	get_height_map(int fd, t_game *game)
{
	int		height;
	char	*line;
	int		len;
	char	*trimmed;

	height = 0;
	line = get_next_line(fd);
	if (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		game->map_width = len;
	}
	while (line != NULL)
	{
		trimmed = ft_strtrim(line, " \t\v\r\f\n");
		if (trimmed && *trimmed != '\0')
			height++;
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

void	new_line(t_game *game, char *trimmed, char *joined)
{
	char	*with_nl;

	if (!trimmed)
	{
		write(2, "Error\nTrimmed", 13);
		free(game->string_map);
		exit(1);
	}
	with_nl = ft_strjoin(trimmed, "\n");
	free(trimmed);
	joined = ft_joinfree(game->string_map, with_nl);
	free(with_nl);
	if (!joined)
	{
		write(2, "Error\nJoin", 11);
		free(game->string_map);
		exit(1);
	}
	game->string_map = joined;
}
