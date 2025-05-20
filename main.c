/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:20:17 by kdrazek           #+#    #+#             */
/*   Updated: 2025/05/20 14:55:37 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (write(2, "Error\nPlease give map.", 22));
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (write(2, "Error\nCalloc", 12));
	structsetter(game);
	map_checker(av[1], game);
	game->map = ft_split(game->string_map, '\n');
	if (!game->map)
		return (1);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_width * 64, game->map_height
			* 64, "so_long");
	load_textures(game);
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	draw_map(game);
	mlx_loop(game->mlx);
}

void	structsetter(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->string_map = ft_strdup("");
	game->map_width = 0;
	game->map_height = 0;
	game->collectible = 0;
	game->moves = 0;
	game->exit_reachable = 0;
}

int	path_valid(char *map_path)
{
	int	i;

	i = ft_strlen(map_path);
	if (i < 5)
		return (1);
	if (map_path[i - 4] != '.' || map_path[i - 3] != 'b'
		|| map_path[i - 2] != 'e' || map_path[i - 1] != 'r')
		return (1);
	return (0);
}

void	map_checker(char *map_path, t_game *game)
{
	int	fd;

	if (path_valid(map_path))
	{
		write(2, "Error\nNot map .ber", 18);
		exit(1);
	}
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nMap read", 14);
		exit(1);
	}
	game->map_height = get_height_map(fd, game);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nMap read", 14);
		exit(1);
	}
	map_load(fd, game, "", "");
}

void	map_load(int fd, t_game *game, char *tmp, char *trimmed)
{
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		trimmed = ft_strtrim(tmp, " \t\v\r\f\n");
		free(tmp);
		if (*trimmed == '\0')
		{
			free(trimmed);
			tmp = get_next_line(fd);
			continue ;
		}
		new_line(game, trimmed, "");
		tmp = get_next_line(fd);
	}
	square(game);
}
