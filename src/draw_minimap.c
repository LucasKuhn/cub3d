/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:23:23 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/20 16:53:56 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static void	draw_cube(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->textures.cube.ptr, x * 10, y * 10);
}

void	draw_minimap(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_cube(game, x, y);
			x++;
		}
		y++;
	}
}
