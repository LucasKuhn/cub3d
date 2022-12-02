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
	mlx_put_image_to_window(game->mlx, game->win, texture, x, y);
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
		d_x += cos(game->direction_in_radian);
		d_y += sin(game->direction_in_radian);
		// mlx_put_image_to_window(game->mlx, game->win, texture, game->player.x + x, game->player.y - y);
		mlx_pixel_put(game->mlx, game->win, game->player.x + d_x, game->player.y - d_y, 0x00FFFFFF);
		i++;
	}
}


void raycast(t_game *game)
{
	int		hit = 0;
	int		n_rays = 0;
	double x_component;
	double y_component;
	double x;
	double y;
	double direction = game->direction_in_radian - -(30 * ONE_RAD);

	while (n_rays < 40)
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
			if (game->map[(int)(y/10)][(int)(x/10)] == '1')
				hit = 1;
			mlx_pixel_put(game->mlx, game->win, x, y, 0x00FF0000);
		}
		n_rays++;
		direction += 2 * ONE_RAD;
	}
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
	/* draw_direction(game); */
	raycast(game);
}
