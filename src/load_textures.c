/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:17:51 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/18 21:18:14 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i][0] != ' ' && game->map[i][0] != '1')
	{
		if (game->map[i][0] == 'C' || game->map[i][0] == 'F')
			set_colors(game, game->map[i]);
		if (game->map[i][0] == 'N' || game->map[i][0] == 'S'
			|| game->map[i][0] == 'W' || game->map[i][0] == 'E')
			set_texture(game, game->map[i]);
		i++;
	}
	while (*(game->map)[0] != ' ' && *(game->map)[0] != '1')
		game->map++;
	game->textures.frame = new_image(game, WIDTH, HEIGHT);
	game->textures.cube = new_xpm(game, "./images/gray10.xpm");
	game->textures.player = new_xpm(game, "./images/yellow3x3.xpm");
}