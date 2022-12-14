#include "./include/cub3d.h"

int close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

int is_movement(int keycode)
{
	return (keycode == W_KEY || keycode == S_KEY || keycode == A_KEY || keycode == D_KEY);
}

int key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == LEFT_ARROW)
	{
		game->player_direction += TURNING_SPEED;
		if (game->player_direction > 360)
			game->player_direction = 0;
		game->direction_in_radian = DEG_TO_RAD(game->player_direction);
	}
	if (keycode == RIGHT_ARROW)
	{
		game->player_direction -= TURNING_SPEED;
		if (game->player_direction < 0)
			game->player_direction = 360;
		game->direction_in_radian = DEG_TO_RAD(game->player_direction);
	}
	if (is_movement(keycode))
		move_player(keycode, game);
	draw_minimap(game);
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
	game.ground = new_xpm(&game, "./images/ground.xpm");
	game.ceiling = new_xpm(&game, "./images/ceiling.xpm");
	game.columns = new_image(&game, 1080, 560);
	/* 	draw_3d_view(&game); */
	/* 	draw_minimap(&game); */
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
	game.player = find_player(&game);
	map_error = get_map_error(game.map);
	if (map_error)
	{
		free_matrix(game.map);
		exit_error(map_error);
	}
	run_game(game);
	return (0);
}
