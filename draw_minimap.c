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

NUM_RAYS = 90;

void draw_3d(double rays[NUM_RAYS], t_game *game)
{
	int n_rays = 0;
	mlx_put_image_to_window(game->mlx, game->win, game->ground.ptr, 0, HEIGHT/2);

	while (n_rays < NUM_RAYS)
	{
		int vertical_offset   = n_rays * WIDTH / NUM_RAYS;
		int horizontal_offset = (HEIGHT / 2) - (3000 / rays[n_rays] / 2);
		
		int column_width = 0;
		while (column_width < WIDTH / NUM_RAYS)
		{
			int column_height = 0;
			int column_projected_height = 3000 / rays[n_rays];
			int column_color = 0x00FFFF00;
			while (column_height < column_projected_height)
			{
				mlx_pixel_put(game->mlx, game->win, column_width + vertical_offset, column_height + horizontal_offset, column_color);
				column_height++;
			}
			column_width++;
		}
		n_rays++;
	}
}

void draw_fov(t_game *game)
{
	int		hit = 0;
	int		n_rays = 0;
	double x_component;
	double y_component;
	double x;
	double y;
	double direction = game->direction_in_radian + (NUM_RAYS / 2 * ONE_RAD);
	
	double rays[90] = {0};

	while (n_rays < NUM_RAYS)
	{
		x_component = cos(direction);
		y_component = sin(direction) * -1;
		x = game->player.x + 1.5;
		y = game->player.y + 1.5;
		hit = 0;
		while (!hit && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		{
			x += x_component;
			y += y_component;
			rays[n_rays] += sqrt(pow(x_component, 2) + pow(y_component, 2));
			mlx_pixel_put(game->mlx, game->win, x, y, 0x00FFBD2D);
			if (game->map[(int)(y/10)][(int)(x/10)] == '1')
				hit = 1;
			// int wall_type = get_wall_type(x, y, game->direction_in_radian);
			// Save what kind of wall was hit
		}
		n_rays++;
		direction -= ONE_RAD;
	}

	// print rays to console for debugging
	// int i = 0;
	// printf("---Rays---\n");
	// while (i < NUM_RAYS)
	// {
	// 	printf("Ray[%d]=%f\n", i, rays[i]);
	// 	i++;
	// }
	draw_3d(rays, game);
}

void draw_minimap(t_game *game)
{
	char *map_line;
	int x, y;

	// skip texture lines
	while (*(game->map)[0] != ' ' && *(game->map)[0] != '1')
		game->map++;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while(game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_cube(game, x * 10, y * 10);
			else
				draw_space(game, x * 10, y * 10);
			x++;
		}
		y++;
	}

	draw_player(game);
	draw_fov(game);
	draw_direction(game);
}
