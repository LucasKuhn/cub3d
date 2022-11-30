#include "./include/cub3d.h"

char *ft_strndup(char *str, int n)
{
	char *ptr;

	ptr = ft_calloc(n + 1, sizeof(char));
	ft_strlcpy(ptr, str, n);
	return (ptr);
}

void	free_matrix(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

int key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == LEFT_ARROW)
		return (0);
	if (keycode == RIGHT_ARROW)
		return (0);
	if (keycode == W_KEY)
		return (0);
	if (keycode == A_KEY)
		return (0);
	if (keycode == S_KEY)
		return (0);
	if (keycode == D_KEY)
		return (0);
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

char	**load_map(char *map_name)
{
	static char	buffer[2];
	char		*map;
	char		*ref;
	int			n_read;
	int			fd;

	fd = open(map_name, O_RDONLY);
	if (fd <= 0)
		return (NULL);
	map = ft_strdup("");
	n_read = 1;
	while (n_read)
	{
		n_read = read(fd, buffer, 1);
		if (n_read == -1)
			return (NULL);
		ref = map;
		map = ft_strjoin(map, buffer);
		free(ref);
	}
	close(fd);
	return (ft_split(map, '\n'));
}

// TODO: THIS IS TRASH! NOT OK! PLEASE FIX ME!
int found_NO = FALSE;
int found_SO = FALSE;
int found_WE = FALSE;
int found_EA = FALSE;
int found_F = FALSE;
int found_C = FALSE;

int	invalid_color(char *map)
{
	char	**colors;
	char	*copy;
	int		info_size;
	int		i;
	int		num;

	info_size = 0;
	i = 0;
	if (*map != 'F' && *map != 'C')
		return (TRUE);
	if (*map == 'F')
		found_F = TRUE;
	if (*map == 'C')
		found_C = TRUE;
	map++;
	while (*map == ' ')
		map++;
	if (!*map)
		return (TRUE);
	while (map[info_size] && map[info_size] != '\n')
		info_size++;
	if (info_size < 5)
		return (TRUE);
	copy = ft_strndup(map, info_size + 1);
	colors = ft_split(copy, ',');
	while (colors[i] != NULL)
	{
		if (i > 2)
		{
			printf("Too many colors\n");
			return (TRUE);
		}
		num = ft_atoi(colors[i]);
		if (num < 0 || num > 255)
		{
			printf("Invalid color '%d'\n", num);
			return (TRUE);
		}
		i++;
	}
	free_matrix(colors);
	free(copy);
	return (FALSE);
}

int	invalid_texture(char *map)
{
	char	*copy;
	int		file_name_size;
	int		fd;

	file_name_size = 0;
	if (ft_strncmp(map, "NO", 2) != 0 && ft_strncmp(map, "SO", 2) != 0
		&& ft_strncmp(map, "WE", 2) != 0 && ft_strncmp(map, "EA", 2) != 0)
	{
		printf("Invalid identifier\n");
		return (TRUE);
	}
	if (ft_strncmp(map, "NO", 2) == 0)
		found_NO = TRUE;
	if (ft_strncmp(map, "SO", 2) == 0)
		found_SO = TRUE;
	if (ft_strncmp(map, "WE", 2) == 0)
		found_WE = TRUE;
	if (ft_strncmp(map, "EA", 2) == 0)
		found_EA = TRUE;
	map += 2;
	while (*map == ' ')
		map++;
	while (map[file_name_size] && map[file_name_size] != '\n')
		file_name_size++;
	copy = ft_strndup(map, file_name_size + 1);
	fd = open(copy, O_RDONLY);
	if (fd < 0)
	{
		printf("Error on texture '%s'\n", copy);
		close(fd);
		free(copy);
		return (TRUE);
	}
	close(fd);
	free(copy);
	return (FALSE);
}

// TODO: Move this to utils
size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

// TODO: Fix this
int surrounded_by_walls(char **map)
{
	int i;
	int j;

	// Replace player for 0
	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(ft_strchr("NSEW", map[i][j]) != NULL)
				map[i][j] = '0';
			j++;
		}
		i++;
	}
	// Turn map into matrix
	int last_line = ft_arrlen(map) - 1;
	// Iterate matrix and check if every 0 is surrounded by other 0 or 1
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				/* printf("Found 0 on [%d][%d]\n", i, j); */
				// Can't have a 0 on the first line or the last line
				if (i == 0 || i == last_line)
					return (FALSE);
				// Can't have an open space to the right
				if (map[i][j + 1] != '1' && map[i][j + 1] != '0')
					return (FALSE);
				// Can't have an open space to the left
				if (map[i][j - 1] != '1' && map[i][j - 1] != '0')
					return (FALSE);
				// Can't have an open space above
				if (ft_strlen(map[i - 1]) < i)
					return (FALSE);
				if (map[i - 1][j] != '1' && map[i - 1][j] != '0')
					return (FALSE);
				// Can't have an open space below
				if (ft_strlen(map[i + 1]) < i)
					return (FALSE);
				if (map[i + 1][j] != '1' && map[i + 1][j] != '0')
					return (FALSE);
			}
			j++;
		}
		i++;
	}
	// TODO: Reload map, since we changed the original
	return (TRUE);
}

int	has_invalid_characters(char **map)
{
	int	i;

	while (*map)
	{
		i = 0;
		while((*map)[i])
		{
			if(ft_strchr("1NWES0 ", (*map)[i]) == NULL)
				return(TRUE);
			i++;
		}
		map++;
	}
	return (FALSE);
}

int has_starting_position(char **map)
{
	int i;

	while (*map)
	{

		i = 0;
		while((*map)[i])
		{
			if(ft_strchr("NSEW", (*map)[i]) != NULL)
				return(TRUE);
			i++;
		}
		map++;
	}
	return (FALSE);
}

char *get_identifier(char *line)
{
	if (ft_strncmp(line,"NO ", 3) == 0)
		return("NO");
	if (ft_strncmp(line,"SO ", 3) == 0)
		return("SO");
	if (ft_strncmp(line,"WE ", 3) == 0)
		return("WE");
	if (ft_strncmp(line,"EA ", 3) == 0)
		return("EA");
	if (ft_strncmp(line,"F ", 2) == 0)
		return("F");
	if (ft_strncmp(line,"C ", 2) == 0)
		return("C");
	return(NULL);
}

int has_all_identifiers(char **map)
{
	static int NO;
	static int SO;
	static int WE;
	static int EA;
	static int F;
	static int C;
	char	*identifier;

	while(*map)
	{
		if (*map[0] == '1' || *map[0] == ' ')
			break;
		identifier = get_identifier(*map);
		if (ft_strncmp(identifier,"NO", 2) == 0)
			NO = TRUE;
		if (ft_strncmp(identifier,"SO", 2) == 0)
			SO = TRUE;
		if (ft_strncmp(identifier,"WE", 2) == 0)
			WE = TRUE;
		if (ft_strncmp(identifier,"EA", 2) == 0)
			EA = TRUE;
		if (ft_strncmp(identifier,"F", 2) == 0)
			F = TRUE;
		if (ft_strncmp(identifier,"C", 2) == 0)
			C = TRUE;
		map++;
	}
	return (NO && SO && WE && EA && F && C);
}

int is_map_start(char *map_line)
{
	return(map_line[0] == '1' || map_line[0] == ' ');
}

char	*get_map_error(char **map)
{
	char		*identifier;
	static int	identifiers_count;
	char		**identifier_found;

	if (!has_all_identifiers(map))
		return("At least 1 identifier is missing");
	while(*map && !is_map_start(*map))
	{
		identifier = get_identifier(*map);
		if (!identifier)
			return("Invalid identifier");
		identifiers_count++;
		if (ft_strlen(identifier) == 2 && invalid_texture(*map))
				return("Invalid texture");
		if (ft_strlen(identifier) == 1 && invalid_color(*map))
				return("Invalid color");
		if (identifiers_count > 6)
				return("Too many identifiers");
		map++;
	}
	if (!has_starting_position(map))
		return("Starting position not present");
	if (has_invalid_characters(map))
		return("Contains invalid characters");
	if (!surrounded_by_walls(map))
		return("Not surrounded by walls");
	return (NULL);
}

int exit_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	exit(1);
}

t_image	new_image(t_game *game, char *path)
{
	t_image	img;

	img.ptr = mlx_xpm_file_to_image(game->mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits, &img.line_size,
			&img.endian);
	return (img);
}

int run_game(t_game game)
{
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	mlx_hook(game.win, BTN_X, NO_EVENT, close_game, &game);
	mlx_key_hook(game.win, key_hook, &game);
	game.ground = new_image(&game, "./images/ground.xpm");
	game.ceiling = new_image(&game, "./images/ceiling.xpm");
	mlx_put_image_to_window(game.mlx, game.win, game.ceiling.ptr, 0, 0);
	mlx_put_image_to_window(game.mlx, game.win, game.ground.ptr, 0, HEIGHT/2);
	mlx_loop(game.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*map_error;

	if (argc < 2)
		exit_error("Please provide a map");
	game.map_name = argv[1];
	if (!valid_extension(game.map_name))
		exit_error("Invalid map extension");
	game.map  = load_map(game.map_name);
	map_error = get_map_error(game.map);
	if (map_error)
	{
		// todo: Free the map
		exit_error(map_error);
	}
	run_game(game);
	return (0);
}
