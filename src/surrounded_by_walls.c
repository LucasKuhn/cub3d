/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrounded_by_walls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:38:03 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/20 16:58:42 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	remove_player(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]) != NULL)
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

static int	line_checker(char **map, size_t i, int j)
{
	if (map[i][j + 1] != '1' && map[i][j + 1] != '0')
		return (FALSE);
	if (map[i][j - 1] != '1' && map[i][j - 1] != '0')
		return (FALSE);
	if (ft_strlen(map[i - 1]) < i)
		return (FALSE);
	if (map[i - 1][j] != '1' && map[i - 1][j] != '0')
		return (FALSE);
	if (ft_strlen(map[i + 1]) < i)
		return (FALSE);
	if (map[i + 1][j] != '1' && map[i + 1][j] != '0')
		return (FALSE);
	return (TRUE);
}

int	surrounded_by_walls(char **map)
{
	int	i;
	int	j;
	int	last_line;

	remove_player(map);
	last_line = ft_arrlen(map) - 1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || i == last_line)
					return (FALSE);
				if (line_checker(map, i, j) == 0)
					return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}
