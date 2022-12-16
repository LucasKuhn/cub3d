#include "./include/cub3d.h"

void render_screen(t_game *game)
{
	t_ray rays[WIDTH] = {0};

	cast_rays(game, rays);
	int i = 0;
	while (i < WIDTH)
	{
		draw_image_column(game, rays[i].size, i, rays[i].color);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->columns.ptr, 0, 0);
	draw_minimap(game);
	draw_player(game);
	draw_direction(game);
}
