/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:26:34 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/20 11:38:18 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	draw_ceiling(t_game *game, int y, int column)
{
	int	pixel;

	pixel = (y * game->textures.frame.line_size) + (column * 4);
	game->textures.frame.pixels[pixel + 0] = game->ceiling[2];
	game->textures.frame.pixels[pixel + 1] = game->ceiling[1];
	game->textures.frame.pixels[pixel + 2] = game->ceiling[0];
	game->textures.frame.pixels[pixel + 3] = 0;
}

void	draw_ground(t_game *game, int y, int column)
{
	int	pixel;

	pixel = (y * game->textures.frame.line_size) + (column * 4);
	game->textures.frame.pixels[pixel + 0] = game->floor[2];
	game->textures.frame.pixels[pixel + 1] = game->floor[1];
	game->textures.frame.pixels[pixel + 2] = game->floor[0];
	game->textures.frame.pixels[pixel + 3] = 0;
}

int get_pixel(t_game *game, int y, int column)
{
	return ((y * game->textures.frame.line_size) + (column * 4));
}

void	draw_wall(t_game *game, t_ray ray, int pixel, int texture_y)
{
		if (pixel > HEIGHT * WIDTH * 4) // Do we need this?
			return ;
		game->textures.frame.pixels[pixel + 0] = ray.texture.pixels[(texture_y * ray.texture.line_size	+ ray.texture_offset_x) + 0];
		game->textures.frame.pixels[pixel + 1] = ray.texture.pixels[(texture_y * ray.texture.line_size	+ ray.texture_offset_x) + 1];
		game->textures.frame.pixels[pixel + 2] = ray.texture.pixels[(texture_y * ray.texture.line_size	+ ray.texture_offset_x) + 2];
		game->textures.frame.pixels[pixel + 3] = ray.texture.pixels[(texture_y * ray.texture.line_size	+ ray.texture_offset_x) + 3];
}

double get_starting_texture_y(t_ray ray, double column_height)
{
	double texture_y;
	double step_y;

	step_y = (ray.texture.size.y / ray.column_height);
	if (column_height < HEIGHT)
		texture_y = 0;
	else
		texture_y = (((ray.texture.size.y / step_y) - HEIGHT) / 2) * step_y;
	return (texture_y);
}

void	draw_column(t_game *game, t_ray ray, int column)
{
	double	column_height;
	int		y;
	double	texture_y;
	double	offset;

	offset = ceil((HEIGHT - ray.column_height) / 2);
	y = 1;
	while (y < offset)
	{
		draw_ceiling(game, y, column);
		y++;
	}
	texture_y = get_starting_texture_y(ray, column_height);
	while (y < HEIGHT - offset)
	{
		draw_wall(game, ray, get_pixel(game, y, column), floor(texture_y));
		texture_y += (ray.texture.size.y / ray.column_height);
		y++;
	}
	while (y < HEIGHT)
	{
		draw_ground(game, y, column);
		y++;
	}
}
