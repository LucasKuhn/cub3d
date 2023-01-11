#include "./include/cub3d.h"

int close_game(t_game *game)
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
	free(game->mlx);
	free_matrix(game->map_original);
	exit(0);
	return (0);
}

int key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (is_direction(keycode))
		change_direction(keycode, game);
	if (is_movement(keycode))
		move_player(keycode, game);
	render_screen(game);
	return (0);
}

int exit_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	exit(1);
}

t_image new_xpm(t_game *game, char *path)
{
	t_image img;

	img.ptr = mlx_xpm_file_to_image(game->mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits, &img.line_size,
								   &img.endian);
	return (img);
}

t_image new_image(t_game *game, int width, int height)
{
	t_image img;

	img.ptr = mlx_new_image(game->mlx, width, height);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits, &img.line_size,
								   &img.endian);
	return (img);
}

int run_game(t_game game)
{
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	mlx_hook(game.win, BTN_X, NO_EVENT, close_game, &game);
	mlx_hook(game.win, 02, 1L << 0, key_hook, &game);
	game.textures.frame = new_image(&game, 1080, 560);
	game.textures.cube = new_xpm(&game, "./images/gray10.xpm");
	game.textures.player = new_xpm(&game, "./images/yellow3x3.xpm");
	game.textures.north = new_xpm(&game, "./images/north.xpm");
	game.textures.south = new_xpm(&game, "./images/south.xpm");
	game.textures.east = new_xpm(&game, "./images/east.xpm");
	game.textures.west = new_xpm(&game, "./images/west.xpm");
	render_screen(&game);
	mlx_loop(game.mlx);
	return (0);
}

int main(int argc, char **argv)
{
	t_game game;
	char *map_error;

	if (argc < 2)
		exit_error("Please provide a map");
	game.map_name = argv[1];
	if (!valid_extension(game.map_name))
		exit_error("Invalid map extension");
	game.map = load_map(game.map_name);
	game.map_original = game.map;
	game.player = find_player(&game);
	map_error = get_map_error(game.map);
	if (map_error)
	{
		free_matrix(game.map);
		exit_error(map_error);
	}
	while (*game.map[0] != ' ' && *game.map[0] != '1')
		game.map++;
	run_game(game);
	return (0);
}
