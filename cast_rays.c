#include "./include/cub3d.h"

int get_wall_color(double direction, int vertical_hit)
{
	if (direction > 0 && direction < M_PI_2 && vertical_hit) // first quadrant
		return (WHITE);
	if (direction > 0 && direction < M_PI_2 || (direction > 2 * M_PI && !vertical_hit)) // first quadrant
		return (BLUE);
	if (direction > M_PI_2 && direction < M_PI && vertical_hit) // second quadrant
		return (YELLOW);
	if (direction > M_PI_2 && direction < M_PI) // second quadrant
		return (BLUE);
	if (direction > M_PI && direction < 3 * M_PI / 2 && vertical_hit) // third quadrant
		return (YELLOW);
	if (direction > M_PI && direction < 3 * M_PI / 2) // third quadrant
		return (GREEN);
	if (vertical_hit) // fourth quadrant
		return (WHITE);
	else // fourth quadrant
		return (GREEN);
}

void cast_rays(t_game *game, t_ray rays[])
{
	int hit = 0;
	int n_rays = 0;
	double x_component;
	double y_component;
	double x;
	double y;
	double fov = (M_PI / 2);
	double direction = game->direction_in_radian + (fov / 2);
	double step_size = fov / WIDTH;
	int vertical_hit;
	while (n_rays < WIDTH)
	{
		x_component = cos(direction) / 40;	// Increasing this value will make the ray step smaller
		y_component = -sin(direction) / 40; // Increasing this value will make the ray step smaller
		x = game->player.x;
		y = game->player.y;
		hit = 0;
		vertical_hit = FALSE;
		while (!hit && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		{
			x += x_component;
			if (game->map[(int)(y / 10)][(int)(x / 10)] == '1')
				vertical_hit = TRUE;
			y += y_component;
			/* 	mlx_pixel_put(game->mlx, game->win, x, y, 0x00FFBD2D); */
			if (game->map[(int)(y / 10)][(int)(x / 10)] == '1')
			{
				hit = 1;
				long double player_ray_difference = game->direction_in_radian - direction;
				// Below is a fisheye fix (the 0.8 is to still keep a small amount if fisheye, avoiding distortion on the sides)
				long double size = sqrt(pow(x - game->player.x, 2) + pow(y - game->player.y, 2)) * (cos(player_ray_difference * 0.8));
				rays[n_rays].size = size;
				rays[n_rays].color = get_wall_color(direction, vertical_hit);
			}
		}
		n_rays++;
		direction -= step_size;
	}
}
