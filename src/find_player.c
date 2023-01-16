/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:06:09 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/16 16:30:19 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_directions(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	map = game->map;
	while (*map[0] != ' ' && *map[0] != '1')
		map++;
	x = game->player.x / 10;
	y = game->player.y / 10;
	if (map[y][x] == 'N')
		game->player_direction = 90;
	if (map[y][x] == 'E')
		game->player_direction = 0;
	if (map[y][x] == 'S')
		game->player_direction = 270;
	if (map[y][x] == 'W')
		game->player_direction = 180;
	game->direction_in_radian = game->player_direction * (M_PI / 180.0);
}

t_vector	find_player(char **map)
{
	t_vector	player;
	int			i;
	int			j;

	while (*map[0] != ' ' && *map[0] != '1')
		map++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				player.x = (j * 10);
				player.y = (i * 10);
				return (player);
			}
			j++;
		}
		i++;
	}
	return (player);
}
