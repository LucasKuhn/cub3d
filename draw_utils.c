#include "./include/cub3d.h"

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
