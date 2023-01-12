#include "./include/cub3d.h"

void	draw_image_column(t_game *game, t_ray ray, int column)
{
	double	column_height;
	int		y;
	double	texture_y;
	double	step_y;
	int		texture_offset_x;
	int		current_texture_y;

	double offset; // difference between the column height and the screen height
	column_height = (HEIGHT / ray.size) * 5;
	offset = ceil((HEIGHT - column_height) / 2);
	y = 1;
	while (y < offset) // THIS DRAWS THE CEILING
	{
		int pixel = (y * game->textures.frame.line_size) + (column * 4);
			// change the 'offset' to top offset the dist
		game->textures.frame.pixels[pixel + 0] = game->ceiling[2];       // blue
		game->textures.frame.pixels[pixel + 1] = game->ceiling[1];      
			// green
		game->textures.frame.pixels[pixel + 2] = game->ceiling[0];       // red
		game->textures.frame.pixels[pixel + 3] = 0;                     
			// alpha
		y++;
	}
	step_y = (ray.texture.size.y / column_height);
	if (column_height < HEIGHT)
		texture_y = 0;
	else // start with an offset
		texture_y = (((ray.texture.size.y / step_y) - HEIGHT) / 2) * step_y;
	while (y < HEIGHT - offset) // THIS DRAWS THE textures.frame
	{
		int pixel = (y * game->textures.frame.line_size) + (column * 4);
			// change the 'offset' to top offset the dist
		if (pixel > HEIGHT * WIDTH * 4)
			break ;
		texture_offset_x = (column % 256) * 4;
		current_texture_y = (int)floor(texture_y);
		game->textures.frame.pixels[pixel
			+ 0] = ray.texture.pixels[(current_texture_y * ray.texture.line_size
				+ texture_offset_x) + 0]; // blue
		game->textures.frame.pixels[pixel
			+ 1] = ray.texture.pixels[(current_texture_y * ray.texture.line_size
				+ texture_offset_x) + 1]; // green
		game->textures.frame.pixels[pixel
			+ 2] = ray.texture.pixels[(current_texture_y * ray.texture.line_size
				+ texture_offset_x) + 2]; // red
		game->textures.frame.pixels[pixel
			+ 3] = ray.texture.pixels[(current_texture_y * ray.texture.line_size
				+ texture_offset_x) + 3]; // alpha
		texture_y += 1 * step_y;
		y++;
	}
	while (y < HEIGHT) // THIS DRAWS THE GROUND
	{
		int pixel = (y * game->textures.frame.line_size) + (column * 4);
			// change the 'offset' to top offset the dist
		game->textures.frame.pixels[pixel + 0] = game->floor[2];         // blue
		game->textures.frame.pixels[pixel + 1] = game->floor[1];        
			// green
		game->textures.frame.pixels[pixel + 2] = game->floor[0];         // red
		game->textures.frame.pixels[pixel + 3] = 0;                     
			// alpha
		y++;
	}
	return ;
}

void	render_screen(t_game *game)
{
	t_ray	rays[WIDTH];
	int		i;

	rays[WIDTH] = {0};
	cast_rays(game, rays);
	i = 0;
	while (i < WIDTH)
	{
		draw_image_column(game, rays[i], i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->textures.frame.ptr, 0,
			0);
	mlx_put_image_to_window(game->mlx, game->win, game->textures.player.ptr,
			game->player.x, game->player.y);
	draw_minimap(game);
	draw_direction(game);
}
