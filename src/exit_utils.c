/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:15:33 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/18 21:15:52 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	exit_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	exit(1);
}

void	exit_map_error(t_game *game, char *map_error)
{
	free_matrix(game->map);
	exit_error(map_error);
}