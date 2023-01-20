/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:22:27 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/20 14:18:30 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

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
