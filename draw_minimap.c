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

// void draw_3d(t_ray rays[WIDTH], t_game *game)
// {
// 	int n_rays = 0;

// 	mlx_put_image_to_window(game->mlx, game->win, game->ground.ptr, 0, HEIGHT / 2);

// 	int column_width = 0;
// 	while (n_rays < WIDTH)
// 	{
// 		int horizontal_offset = (HEIGHT / 2) - (3000 / rays[n_rays].size / 2);

// 		int column_height = 0;
// 		int column_projected_height = 3000 / rays[n_rays].size;
// 		int column_color = rays[n_rays].color;
// 		while (column_height < column_projected_height)
// 		{
// 			mlx_pixel_put(game->mlx, game->win, column_width, column_height + horizontal_offset, column_color);
// 			column_height++;
// 		}
// 		column_width++;
// 		n_rays++;
// 	}
// }

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
