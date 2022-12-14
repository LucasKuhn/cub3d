#include "./include/cub3d.h"

void draw_cube(t_game *game, int x, int y)
{
	int i;
	int j;
	static void *texture;

	if (!texture)
		texture = mlx_xpm_file_to_image(game->mlx, "./images/gray10.xpm", &i, &j);
	mlx_put_image_to_window(game->mlx, game->win, texture, x, y);
}

void draw_space(t_game *game, int x, int y)
{
	int i;
	int j;
	static void *texture;

	if (!texture)
		texture = mlx_xpm_file_to_image(game->mlx, "./images/black10.xpm", &i, &j);
	// mlx_put_image_to_window(game->mlx, game->win, texture, x, y);
}

void draw_player(t_game *game)
{
	int x;
	int y;

	static void *texture;

	if (!texture)
		texture = mlx_xpm_file_to_image(game->mlx, "./images/yellow3x3.xpm", &x, &y);
	mlx_put_image_to_window(game->mlx, game->win, texture, game->player.x, game->player.y);
}

void draw_direction(t_game *game)
{
	int x;
	int y;

	static void *texture;

	if (!texture)
		texture = mlx_xpm_file_to_image(game->mlx, "./images/white.xpm", &x, &y);

	int i = 0;
	double d_x = 0;
	double d_y = 0;
	while (i < 10)
	{
		d_x += cos(game->direction_in_radian + M_PI);
		d_y += sin(game->direction_in_radian + M_PI);
		// mlx_put_image_to_window(game->mlx, game->win, texture, game->player.x + x, game->player.y - y);
		mlx_pixel_put(game->mlx, game->win, game->player.x + d_x, game->player.y - d_y, 0x00FFFFFF);
		i++;
	}
}

typedef struct s_ray
{
	double size;
	int color; // Change this to reference a texture
} t_ray;

void draw_3d(t_ray rays[WIDTH], t_game *game)
{
	int n_rays = 0;

	mlx_put_image_to_window(game->mlx, game->win, game->ground.ptr, 0, HEIGHT / 2);

	int column_width = 0;
	while (n_rays < WIDTH)
	{
		int horizontal_offset = (HEIGHT / 2) - (3000 / rays[n_rays].size / 2);

		int column_height = 0;
		int column_projected_height = 3000 / rays[n_rays].size;
		int column_color = rays[n_rays].color;
		while (column_height < column_projected_height)
		{
			mlx_pixel_put(game->mlx, game->win, column_width, column_height + horizontal_offset, column_color);
			column_height++;
		}
		column_width++;
		n_rays++;
	}
}

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

void draw_fov(t_game *game)
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
	t_ray rays[WIDTH] = {0};
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
	int i = 0;
	while (i < WIDTH)
	{
		draw_image_column(game, rays[i].size, i, rays[i].color);
		i++;
	}
	/* 	draw_3d(rays, game); */
}

void draw_minimap(t_game *game)
{
	char *map_line;
	int x, y;

	// skip texture lines
	while (*(game->map)[0] != ' ' && *(game->map)[0] != '1')
		game->map++;
	y = 0;
	draw_fov(game);
	mlx_put_image_to_window(game->mlx, game->win, game->columns.ptr, 0, 0);
	draw_player(game);
	draw_direction(game);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_cube(game, x * 10, y * 10);
			else
				draw_space(game, x * 10, y * 10);
			x++;
		}
		y++;
	}
}
