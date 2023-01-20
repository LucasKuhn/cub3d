/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:20:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/20 14:22:12 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	render_screen(t_game *game)
{
	int	i;

	cast_rays(game);
	i = 0;
	while (i < WIDTH)
	{
		draw_column(game, game->rays[i], i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->textures.frame.ptr, 0,
		0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures.player.ptr,
		game->player.x, game->player.y);
	draw_minimap(game);
	draw_direction(game);
}
