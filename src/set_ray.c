/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:17:52 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/20 16:28:47 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static t_image	get_wall_texture(t_game *game, double direction,
		int vertical_hit)
{
	if (direction > 0 && direction < M_PI_2 && vertical_hit)
		return (game->textures.south);
	if (direction > 0 && direction < M_PI_2 || (direction > 2 * M_PI
			&& !vertical_hit))
		return (game->textures.west);
	if (direction > M_PI_2 && direction < M_PI && vertical_hit)
		return (game->textures.north);
	if (direction > M_PI_2 && direction < M_PI)
		return (game->textures.west);
	if (direction > M_PI && direction < 3 * M_PI / 2 && vertical_hit)
		return (game->textures.north);
	if (direction > M_PI && direction < 3 * M_PI / 2)
		return (game->textures.east);
	if (vertical_hit)
		return (game->textures.south);
	else
		return (game->textures.east);
}

static int	get_texture_offset_x(t_ray ray)
{
	int	texture_offset_x;

	if (ray.vertical_hit)
		texture_offset_x = (int)((ray.y * ray.texture.size.x) / 10) % 256 * 4;
	else
		texture_offset_x = (int)((ray.x * ray.texture.size.x) / 10) % 256 * 4;
	return (texture_offset_x);
}

static double	get_texture_offset_y(t_ray ray)
{
	double	texture_y;
	double	step_y;

	step_y = (ray.texture.size.y / ray.column_height);
	if (ray.column_height < HEIGHT)
		texture_y = 0;
	else
		texture_y = (((ray.texture.size.y / step_y) - HEIGHT) / 2) * step_y;
	return (texture_y);
}

static double	get_size(t_game *game, t_ray *ray, double dir)
{
	long double	size;
	long double	fisheye_fix;
	double		x;
	double		y;

	x = ray->x - game->player.x;
	y = ray->y - game->player.y;
	size = sqrt(pow(x, 2) + pow(y, 2));
	fisheye_fix = cos((game->direction_in_radian - dir) * 0.85);
	size = size * fisheye_fix;
	return (size);
}

void	set_ray(t_game *game, t_ray *ray, int vertical_hit, double dir)
{
	ray->vertical_hit = vertical_hit;
	ray->size = get_size(game, ray, dir);
	ray->column_height = (HEIGHT / ray->size) * WALL_HEIGHT;
	ray->texture = get_wall_texture(game, dir, vertical_hit);
	ray->texture_offset_x = get_texture_offset_x(*ray);
	ray->texture_offset_y = get_texture_offset_y(*ray);
}
