/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:07:22 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/20 15:53:36 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	cub3d(char *map_name)
{
	t_game	game;
	char	*map_error;

	load_map(&game, map_name);
	set_player(&game);
	map_error = get_map_error(game.map);
	if (map_error)
		exit_map_error(&game, map_error);
	game.rays = malloc(WIDTH * sizeof(t_ray));
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	load_textures(&game);
	mlx_hook(game.win, BTN_X, NO_EVENT, close_game, &game);
	mlx_hook(game.win, 02, 1L << 0, key_hook, &game);
	render_screen(&game);
	mlx_loop(game.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		exit_error("Please provide a map");
	if (!valid_extension(argv[1]))
		exit_error("Invalid map extension");
	return (cub3d(argv[1]));
}
