# include <mlx.h> // MiniLibX
# include <stdlib.h>
#include <stdio.h> // printf
#include "libft/libft.h" // libft

# define KEY_ESC 65307
# define BTN_X 17
# define NO_EVENT 0L
# define TRUE 1
# define FALSE 0

void			*mlx;
void			*win;

int	close_game()
{
	mlx_destroy_window(mlx, win);
	exit(0);
}

int key_hook(int keycode)
{
	if (keycode == KEY_ESC)
		close_game();
	return (0);
}

int valid_extension(char *map_name)
{
	char	*extension;

	extension = ft_strrchr(map_name, '.');
	if (!extension || ft_strncmp(extension, ".cub", 4) != 0)
		return (FALSE);
	return (TRUE);
}

int is_valid(char *map_name)
{
	if (!valid_extension(map_name))
		return (FALSE);
	return(TRUE);
}

int	main(int argc, char **argv)
{
	char *map_name;

	map_name = argv[1];

	if (!is_valid(map_name))
	{
		printf("Invalid map: %s\n", map_name);
		exit(1);
	}
	mlx = mlx_init();
	win = mlx_new_window(mlx, 200, 200, "cub3D");
	mlx_hook(win, BTN_X, NO_EVENT, close_game, NULL);
	mlx_key_hook(win, key_hook, NULL);
	mlx_loop(mlx);
	return (0);
}
