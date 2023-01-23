/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:20:36 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/23 20:56:26 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	render_screen(t_game *game)
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
	return (TRUE);
}
