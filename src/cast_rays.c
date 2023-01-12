#include "./include/cub3d.h"

t_image	get_wall_texture(t_game *game, double direction, int vertical_hit)
{
	if (direction > 0 && direction < M_PI_2
		&& vertical_hit)                            // first quadrant
		return (game->textures.south);                                                 
		// south
	if (direction > 0 && direction < M_PI_2 || (direction > 2 * M_PI
			&& !vertical_hit)) // first quadrant
		return (game->textures.west);                                                  
		// west
	if (direction > M_PI_2 && direction < M_PI
		&& vertical_hit)                         // second quadrant
		return (game->textures.north);                                                 
		// north
	if (direction > M_PI_2
		&& direction < M_PI)                                        
	// second quadrant
		return (game->textures.west);                                                  
		// west
	if (direction > M_PI && direction < 3 * M_PI / 2
		&& vertical_hit)                   // third quadrant
		return (game->textures.north);                                                 
		// north
	if (direction > M_PI && direction < 3 * M_PI
		/ 2)                                   // third quadrant
		return (game->textures.east);                                                  
		// east
	if (vertical_hit)                                                                  
	// fourth quadrant
		return (game->textures.south);                                                 
		// south
	else                                                                               
		// fourth quadrant
		return (game->textures.east);                                                  
		// east
}

void	cast_rays(t_game *game, t_ray rays[])
{
	int			hit;
	int			n_rays;
	double		x_component;
	double		y_component;
	double		x;
	double		y;
	double		fov;
	double		direction;
	double		step_size;
	int			vertical_hit;
	long double	player_ray_difference;
	long double	size;

	hit = 0;
	n_rays = 0;
	fov = (M_PI / 2);
	direction = game->direction_in_radian + (fov / 2);
	step_size = fov / WIDTH;
	while (n_rays < WIDTH)
	{
		x_component = cos(direction) / 30; 
			// Increasing this value will make the ray step smaller
		y_component = -sin(direction) / 30;
			// Increasing this value will make the ray step smaller
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
				player_ray_difference = game->direction_in_radian - direction;
				long double fisheye_fix = cos(player_ray_difference * 0.8);
					// 0.8 keeps a small amount of fisheye,
					avoiding distortion on the sides
				size = sqrt(pow(x - game->player.x, 2) + pow(y - game->player.y,
							2)) * fisheye_fix;
				rays[n_rays].size = size;
				rays[n_rays].texture = get_wall_texture(game, direction,
						vertical_hit);
			}
		}
		n_rays++;
		direction -= step_size;
	}
}
