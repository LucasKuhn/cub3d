/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:24:50 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/20 16:55:25 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static double	get_rad(t_game *game, int keycode)
{
	double	rad;

	if (keycode == W_KEY)
		rad = game->direction_in_radian + 0;
	if (keycode == S_KEY)
		rad = game->direction_in_radian + M_PI;
	if (keycode == A_KEY)
		rad = game->direction_in_radian + (M_PI / 2);
	if (keycode == D_KEY)
		rad = game->direction_in_radian - (M_PI / 2);
	return (rad);
}

void	change_direction(int keycode, t_game *game)
{
	if (keycode == LEFT_ARROW)
	{
		game->player_direction += TURNING_SPEED;
		if (game->player_direction > 360)
			game->player_direction = 0;
		game->direction_in_radian = game->player_direction * (M_PI / 180.0);
	}
	if (keycode == RIGHT_ARROW)
	{
		game->player_direction -= TURNING_SPEED;
		if (game->player_direction < 0)
			game->player_direction = 360;
		game->direction_in_radian = game->player_direction * (M_PI / 180.0);
	}
}

void	move_player(int keycode, t_game *game)
{
	double	x_component;
	double	y_component;
	double	rad;

	rad = get_rad(game, keycode);
	x_component = cos(rad) * MOVING_SPEED;
	y_component = sin(rad) * MOVING_SPEED;
	game->player.y = game->player.y - 1 * y_component;
	game->player.x = game->player.x + 1 * x_component;
}

int	can_move_player(int keycode, t_game *game)
{
	double	x_component;
	double	y_component;
	int		new_player_x;
	int		new_player_y;
	double	rad;

	rad = get_rad(game, keycode);
	x_component = cos(rad) * MOVING_SPEED;
	y_component = sin(rad) * MOVING_SPEED;
	new_player_y = (game->player.y - 1 * y_component);
	new_player_x = (game->player.x + 1 * x_component);
	if (game->map[new_player_y / 10][new_player_x / 10] == '1')
		return (FALSE);
	if (game->map[(new_player_y + 1) / 10][(new_player_x + 1) / 10] == '1')
		return (FALSE);
	if (game->map[(new_player_y - 1) / 10][(new_player_x - 1) / 10] == '1')
		return (FALSE);
	if (game->map[(new_player_y + 1) / 10][(new_player_x - 1) / 10] == '1')
		return (FALSE);
	if (game->map[(new_player_y - 1) / 10][(new_player_x + 1) / 10] == '1')
		return (FALSE);
	return (TRUE);
}
