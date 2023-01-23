/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:06:53 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/18 21:14:30 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	is_movement(int keycode)
{
	return (keycode == W_KEY || keycode == S_KEY || keycode == A_KEY
		|| keycode == D_KEY);
}

int	is_direction(int keycode)
{
	return (keycode == LEFT_ARROW || keycode == RIGHT_ARROW);
}

int	is_map_start(char *map_line)
{
	return (map_line[0] == '1' || map_line[0] == ' ');
}
