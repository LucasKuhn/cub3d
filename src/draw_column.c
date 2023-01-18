/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:26:34 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/18 21:50:47 by lucferna         ###   ########.fr       */
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

void	draw_wall(t_game *game, int y, int column)
{
	int	pixel;

	pixel = (y * game->textures.frame.line_size) + (column * 4);
	if (pixel > HEIGHT * WIDTH * 4)
		break ;
	current_texture_y = (int)floor(texture_y);
	game->textures.frame.pixels[pixel + 0] = ray.texture.pixels[(current_texture_y * ray.texture.line_size + texture_offset_x) + 0];
	game->textures.frame.pixels[pixel + 1] = ray.texture.pixels[(current_texture_y * ray.texture.line_size + texture_offset_x) + 1];
	game->textures.frame.pixels[pixel + 2] = ray.texture.pixels[(current_texture_y * ray.texture.line_size + texture_offset_x) + 2];
	game->textures.frame.pixels[pixel + 3] = ray.texture.pixels[(current_texture_y * ray.texture.line_size + texture_offset_x) + 3];
	texture_y += 1 * step_y;
}

void	draw_image_column(t_game *game, t_ray ray, int column)
{
	double	column_height;
	int		y;
	double	texture_y;
	double	step_y;
	int		texture_offset_x;
	int		current_texture_y;
	int		pixel;
	double offset;

	column_height = (HEIGHT / ray.size) * 15;
	offset = ceil((HEIGHT - column_height) / 2);
	y = 1;
	while (y < offset)
	{
		draw_ceiling(game, y, column);
		y++;
	}
	step_y = (ray.texture.size.y / column_height);
	if (column_height < HEIGHT)
		texture_y = 0;
	else
		texture_y = (((ray.texture.size.y / step_y) - HEIGHT) / 2) * step_y;
	if (ray.vertical_hit)
		texture_offset_x = (int)((ray.y * ray.texture.size.x) / 10) % 256 * 4;
	else
		texture_offset_x = (int)((ray.x * ray.texture.size.x) / 10) % 256 * 4;
	while (y < HEIGHT - offset)
	{
		draw_wall(game, y, column);
		y++;
	}
	while (y < HEIGHT)
	{
		draw_ground(game, y, column);
		y++;
	}
	return ;
}