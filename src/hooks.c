/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:10:38 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/18 21:11:20 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->textures.north.ptr);
	mlx_destroy_image(game->mlx, game->textures.south.ptr);
	mlx_destroy_image(game->mlx, game->textures.west.ptr);
	mlx_destroy_image(game->mlx, game->textures.east.ptr);
	mlx_destroy_image(game->mlx, game->textures.frame.ptr);
	mlx_destroy_image(game->mlx, game->textures.player.ptr);
	mlx_destroy_image(game->mlx, game->textures.cube.ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_matrix(game->map_original);
	free(game->rays);
	free(game->mlx);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (is_direction(keycode))
		change_direction(keycode, game);
	if (is_movement(keycode))
	{
		if (can_move_player(keycode, game))
			move_player(keycode, game);
	}
	render_screen(game);
	return (0);
}
