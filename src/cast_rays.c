/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:22:27 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/20 11:23:39 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

t_image	get_wall_texture(t_game *game, double direction, int vertical_hit)
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

static void	set_ray(t_game *game, t_ray *ray, int vertical_hit, double dir)
{
	long double	size;
	long double	fisheye_fix;

	fisheye_fix = cos((game->direction_in_radian - dir) * 0.8);
	size = sqrt(pow(ray->x - game->player.x, 2) + pow(ray->y - game->player.y, 2)) * fisheye_fix;
	ray->size = size;
	ray->texture = get_wall_texture(game, dir, vertical_hit);
	ray->vertical_hit = vertical_hit;
	ray->column_height = (HEIGHT / ray->size) * 15;
	if (vertical_hit)
		ray->texture_offset_x = (int)((ray->y * ray->texture.size.x) / 10) % 256 * 4;
	else
		ray->texture_offset_x = (int)((ray->x * ray->texture.size.x) / 10) % 256 * 4;
}

void	cast_ray(t_game *game, int n_rays, double direction)
{
	t_ray	*ray;
	double	x_component;
	double	y_component;

	x_component = cos(direction) / 30;
	y_component = -sin(direction) / 30;
	ray = &(game->rays[n_rays]);
	ray->x = game->player.x;
	ray->y = game->player.y;
	while (ray->x > 0 && ray->x < WIDTH && ray->y > 0 && ray->y < HEIGHT)
	{
		ray->x += x_component;
		if (game->map[(int)(ray->y / 10)][(int)(ray->x / 10)] == '1')
		{
			set_ray(game, ray, TRUE, direction);
			break ;
		}
		ray->y += y_component;
		if (game->map[(int)(ray->y / 10)][(int)(ray->x / 10)] == '1')
		{
			set_ray(game, ray, FALSE, direction);
			break ;
		}
	}
}

void	cast_rays(t_game *game)
{
	int			n_rays;
	double		direction;

	n_rays = 0;
	direction = game->direction_in_radian + (FOV / 2);
	while (n_rays < WIDTH)
	{
		cast_ray(game, n_rays, direction);
		n_rays++;
		direction -= (FOV / WIDTH);
	}
}
