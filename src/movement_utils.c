#include "./include/cub3d.h"

void	change_direction(int keycode, t_game *game)
{
	if (keycode == LEFT_ARROW)
	{
		game->player_direction += TURNING_SPEED;
		if (game->player_direction > 360)
			game->player_direction = 0;
		game->direction_in_radian = DEG_TO_RAD(game->player_direction);
	}
	if (keycode == RIGHT_ARROW)
	{
		game->player_direction -= TURNING_SPEED;
		if (game->player_direction < 0)
			game->player_direction = 360;
		game->direction_in_radian = DEG_TO_RAD(game->player_direction);
	}
}

void	move_player(int keycode, t_game *game)
{
	double	x_component;
	double	y_component;
	int		new_player_x;
	int		new_player_y;
	double	rad;

	x_component = cos(game->direction_in_radian) * MOVING_SPEED;
	y_component = sin(game->direction_in_radian) * MOVING_SPEED;
	if (keycode == W_KEY)
	{
		new_player_y = game->player.y - 1 * y_component;
		new_player_x = game->player.x + 1 * x_component;
	}
	if (keycode == S_KEY)
	{
		new_player_y = game->player.y + 1 * y_component;
		new_player_x = game->player.x - 1 * x_component;
	}
	if (keycode == A_KEY)
	{
		rad = game->direction_in_radian + (M_PI / 2);
		x_component = cos(rad) * (MOVING_SPEED / 2);
		y_component = sin(rad) * (MOVING_SPEED / 2);
		new_player_y = game->player.y - 1 * y_component;
		new_player_x = game->player.x + 1 * x_component;
	}
	if (keycode == D_KEY)
	{
		rad = game->direction_in_radian - (M_PI / 2);
		x_component = cos(rad) * (MOVING_SPEED / 2);
		y_component = sin(rad) * (MOVING_SPEED / 2);
		new_player_y = game->player.y - 1 * y_component;
		new_player_x = game->player.x + 1 * x_component;
	}
	if (game->map[new_player_y / 10][new_player_x / 10] != '1')
	{
		game->player.y = new_player_y;
		game->player.x = new_player_x;
	}
}
