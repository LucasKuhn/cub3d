/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:15:33 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/20 15:13:06 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	exit_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	exit(0);
}

void	exit_map_error(t_game *game, char *map_error)
{
	free_matrix(game->map);
	exit_error(map_error);
}
