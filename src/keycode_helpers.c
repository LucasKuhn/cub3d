#include "./include/cub3d.h"

int	is_movement(int keycode)
{
	return (keycode == W_KEY || keycode == S_KEY || keycode == A_KEY
		|| keycode == D_KEY);
}

int	is_direction(int keycode)
{
	return (keycode == LEFT_ARROW || keycode == RIGHT_ARROW);
}
