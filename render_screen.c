#include "./include/cub3d.h"

void draw_image_column(t_game *game, t_ray ray, int column)
{
	int ground_color = 0x5e3306;
	int sky_color = 0x06c5cf;
	double column_height;
	double offset; // column height

	printf("ray.size: %f\n", ray.size);
	printf("Column height: %f\n", column_height);
	column_height = (1 / ray.size) * 1500;
	offset = ceil((HEIGHT - column_height) / 2);
	int y = 1;
	while (y < offset) // THIS DRAWS THE GROUND
	{
		int pixel = (y * game->columns.line_size) + (column * 4); // change the 'offset' to top offset the dist

		game->columns.pixels[pixel + 0] = (ground_color);	// blue
		game->columns.pixels[pixel + 1] = (ground_color >> 8);	// green
		game->columns.pixels[pixel + 2] = (ground_color >> 16);	// red
		game->columns.pixels[pixel + 3] = 0;	// alpha
		y++;
	}
	double texture_y;
	if (column_height < HEIGHT)
		texture_y = 0;
	else // start with an offset
		texture_y = column_height;
	printf("texture_y: %f\n", texture_y);
	double step_y = (256 / column_height);
	while (y < HEIGHT - offset) // THIS DRAWS THE COLUMNS
	{
		int pixel = (y * game->columns.line_size) + (column * 4); // change the 'offset' to top offset the dist
		int texture_offset_x = (column % 256) * 4;
		int current_texture_y = (int)floor(texture_y);

		game->columns.pixels[pixel + 0] = ray.texture.pixels[(current_texture_y * ray.texture.line_size + texture_offset_x) + 0];	// blue
		game->columns.pixels[pixel + 1] = ray.texture.pixels[(current_texture_y * ray.texture.line_size + texture_offset_x) + 1];	// green
		game->columns.pixels[pixel + 2] = ray.texture.pixels[(current_texture_y * ray.texture.line_size + texture_offset_x) + 2];	// red
		game->columns.pixels[pixel + 3] = ray.texture.pixels[(current_texture_y * ray.texture.line_size + texture_offset_x) + 3];	// alpha
		texture_y += 1 * step_y;
		y++;
	}
	while (y < HEIGHT) // THIS DRAWS THE SKY
	{
		int pixel = (y * game->columns.line_size) + (column * 4); // change the 'offset' to top offset the dist

		game->columns.pixels[pixel + 0] = (sky_color);		// blue
		game->columns.pixels[pixel + 1] = (sky_color >> 8);	// green
		game->columns.pixels[pixel + 2] = (sky_color >> 16);	// red
		game->columns.pixels[pixel + 3] = 0;	// alpha
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
