/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:22:27 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/18 20:24:48 by lucferna         ###   ########.fr       */
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

static void	set_ray(t_game *game, int n_rays, int vertical_hit,
				double direction)
{
	long double	size;
	long double	fisheye_fix;
	long double	player_ray_difference;

	player_ray_difference = game->direction_in_radian - direction;
	fisheye_fix = cos(player_ray_difference * 0.8);
	size = sqrt(pow(game->rays[n_rays].x - game->player.x, 2)
			+ pow(game->rays[n_rays].y - game->player.y, 2)) * fisheye_fix;
	game->rays[n_rays].size = size;
	game->rays[n_rays].texture = get_wall_texture(game, direction,
			vertical_hit);
	game->rays[n_rays].vertical_hit = vertical_hit;
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
			set_ray(game, n_rays, TRUE, direction);
			break ;
		}
		ray->y += y_component;
		if (game->map[(int)(ray->y / 10)][(int)(ray->x / 10)] == '1')
		{
			set_ray(game, n_rays, FALSE, direction);
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
