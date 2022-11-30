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
	void	*player = mlx_xpm_file_to_image(game->mlx, "./images/yellow3x3.xpm", &x, &y);
	mlx_put_image_to_window(game->mlx, game->win, player, game->player.x, game->player.y);

	// THIS IS UGLY 🤮
	double x_component = cos(game->direction_in_radian);
	double y_component = sin(game->direction_in_radian);

	void	*cross = mlx_xpm_file_to_image(game->mlx, "./images/white.xpm", &x, &y);
	int cross_x = game->player.x + (x_component * 10);
	int cross_y = game->player.y - (y_component * 10);
	mlx_put_image_to_window(game->mlx, game->win, cross, cross_x, cross_y);
}
