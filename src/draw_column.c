/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:26:34 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/20 16:42:14 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	get_pixel(t_game *game, int y, int column)
{
	return ((y * game->textures.frame.line_size) + (column * 4));
}

void	draw_ceiling(t_game *game, int pixel)
{
	t_image	frame;

	frame = game->textures.frame;
	frame.pixels[pixel + 0] = game->ceiling[2];
	frame.pixels[pixel + 1] = game->ceiling[1];
	frame.pixels[pixel + 2] = game->ceiling[0];
	frame.pixels[pixel + 3] = 0;
}

void	draw_ground(t_game *game, int pixel)
{
	t_image	frame;

	frame = game->textures.frame;
	frame.pixels[pixel + 0] = game->floor[2];
	frame.pixels[pixel + 1] = game->floor[1];
	frame.pixels[pixel + 2] = game->floor[0];
	frame.pixels[pixel + 3] = 0;
}

void	draw_wall(t_game *game, t_ray ray, int pixel, int texture_y)
{
	t_image	frame;
	int		texture_pixel;

	frame = game->textures.frame;
	texture_pixel = (texture_y * ray.texture.line_size + ray.texture_offset_x);
	frame.pixels[pixel + 0] = ray.texture.pixels[texture_pixel + 0];
	frame.pixels[pixel + 1] = ray.texture.pixels[texture_pixel + 1];
	frame.pixels[pixel + 2] = ray.texture.pixels[texture_pixel + 2];
	frame.pixels[pixel + 3] = ray.texture.pixels[texture_pixel + 3];
}

void	draw_column(t_game *game, t_ray ray, int column)
{
	int		y;
	double	texture_y;
	double	offset;

	offset = ceil((HEIGHT - ray.column_height) / 2);
	y = 0;
	while (y < offset)
	{
		draw_ceiling(game, get_pixel(game, y, column));
		y++;
	}
	texture_y = ray.texture_offset_y;
	while (y < HEIGHT && y < (HEIGHT - offset))
	{
		draw_wall(game, ray, get_pixel(game, y, column), texture_y);
		texture_y += (ray.texture.size.y / ray.column_height);
		y++;
	}
	while (y < HEIGHT)
	{
		draw_ground(game, get_pixel(game, y, column));
		y++;
	}
}
