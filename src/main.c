#include "./include/cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->textures.north.ptr);
	mlx_destroy_image(game->mlx, game->textures.south.ptr);
	mlx_destroy_image(game->mlx, game->textures.west.ptr);
	mlx_destroy_image(game->mlx, game->textures.east.ptr);
	mlx_destroy_image(game->mlx, game->textures.frame.ptr);
	mlx_destroy_image(game->mlx, game->textures.player.ptr);
	mlx_destroy_image(game->mlx, game->textures.cube.ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free_matrix(game->map_original);
	free(game->mlx);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (is_direction(keycode))
		change_direction(keycode, game);
	if (is_movement(keycode))
	{
		if (can_move_player(keycode,game))
			move_player(keycode, game);
	}
	render_screen(game);
	return (0);
}

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

t_image	new_xpm(t_game *game, char *path)
{
	t_image	img;

	img.ptr = mlx_xpm_file_to_image(game->mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits, &img.line_size,
			&img.endian);
	return (img);
}

int cub3d(char *map_name)
{
	t_game	game;
	char	*map_error;

	game.map = load_map(map_name);
	game.map_original = load_map(map_name);
	game.player = find_player(&game);
	map_error = get_map_error(game.map);
	if (map_error)
		exit_map_error(&game, map_error);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	load_textures(&game);
	mlx_hook(game.win, BTN_X, NO_EVENT, close_game, &game);
	mlx_hook(game.win, 02, 1L << 0, key_hook, &game);render_screen(&game);
	mlx_loop(game.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		exit_error("Please provide a map");
	if (!valid_extension(argv[1]))
		exit_error("Invalid map extension");
	return(cub3d(argv[1]));
}
