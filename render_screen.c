#include "./include/cub3d.h"

void draw_image_column(t_game *game, t_ray ray, int column)
{
	int ground_color = 0x5e3306;
	int sky_color = 0x06c5cf;
	double column_height;
	double offset; // column height

	column_height = (1 / ray.size) * 1500;
	offset = ceil((HEIGHT - column_height) / 2);
	if (offset <= 0)
		offset = 5.0;
	int y = 1;
	while (y < offset) // THIS DRAWS THE GROUND
	{
		int pixel = (y * game->columns.line_size) + (column * 4); // change the 'offset' to top offset the dist

		game->columns.pixels[pixel + 0] = (ground_color)&0xFF;		   // blue
		game->columns.pixels[pixel + 1] = (ground_color >> 8) & 0xFF;  // green
		game->columns.pixels[pixel + 2] = (ground_color >> 16) & 0xFF; // red
		game->columns.pixels[pixel + 3] = 0;						   // alpha
		y++;
	}
	while (y < HEIGHT - offset) // THIS DRAWS THE COLUMNS
	{
		int pixel = (y * game->columns.line_size) + (column * 4); // change the 'offset' to top offset the dist

		// int	pixel_color = texture.dump[(offset_y * texture.width) + offset_x];
		int texture_offset_x = (column % 256) * 4;
		
		game->columns.pixels[pixel + 0] = ray.texture.pixels[((y - (int)offset) * ray.texture.line_size + texture_offset_x) + 0];			// blue
		game->columns.pixels[pixel + 1] = ray.texture.pixels[((y - (int)offset) * ray.texture.line_size + texture_offset_x) + 1];			// green
		game->columns.pixels[pixel + 2] = ray.texture.pixels[((y - (int)offset) * ray.texture.line_size + texture_offset_x) + 2];			// red
		game->columns.pixels[pixel + 3] = ray.texture.pixels[((y - (int)offset) * ray.texture.line_size + texture_offset_x) + 3];			// alpha
		y++;
	}
	while (y < HEIGHT) // THIS DRAWS THE SKY
	{
		int pixel = (y * game->columns.line_size) + (column * 4); // change the 'offset' to top offset the dist

		game->columns.pixels[pixel + 0] = (sky_color)&0xFF;			// blue
		game->columns.pixels[pixel + 1] = (sky_color >> 8) & 0xFF;	// green
		game->columns.pixels[pixel + 2] = (sky_color >> 16) & 0xFF; // red
		game->columns.pixels[pixel + 3] = 0;						// alpha
		y++;
	}
	return;
}

void render_screen(t_game *game)
{
	t_ray rays[WIDTH] = {0};

	cast_rays(game, rays);
	int i = 0;
	while (i < WIDTH)
	{
		draw_image_column(game, rays[i], i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->columns.ptr, 0, 0);
	draw_minimap(game);
	draw_player(game);
	draw_direction(game);
}
