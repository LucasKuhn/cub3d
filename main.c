# include <mlx.h> // MiniLibX
# include <stdlib.h>
#include <stdio.h> // printf
#include "libft/libft.h" // libft
#include <fcntl.h> // open

# define KEY_ESC 65307
# define BTN_X 17
# define NO_EVENT 0L
# define TRUE 1
# define FALSE 0

void			*mlx;
void			*win;

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

int	close_game()
{
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
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

char	*load_map(char *map, int fd)
{
	static char	buffer[2];
	char		*ref;
	int			n_read;

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
	return (map);
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

int any_identifier_missing(void)
{
	if (found_NO == FALSE)
	{
		printf("Missing NO\n");
		return (TRUE);
	}
	if (found_SO == FALSE)
	{
		printf("Missing SO\n");
		return (TRUE);
	}
	if (found_WE == FALSE)
	{
		printf("Missing WE\n");
		return (TRUE);
	}
	if (found_EA == FALSE)
	{
		printf("Missing EA\n");
		return (TRUE);
	}
	if (found_F == FALSE)
	{
		printf("Missing F\n");
		return (TRUE);
	}
	if (found_C == FALSE)
	{
		printf("Missing C\n");
		return (TRUE);
	}
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

int surrounded_by_walls(char *map)
{
	int i;
	int j;

	// Replace player for 0
	i = 0;
	while (map[i])
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'E' || map[i] == 'W')
			map[i] = '0';
		i++;
	}
	// Turn map into matrix 
	char **array;
	array = ft_split(map, '\n');
	int last_line = ft_arrlen(array) - 1;
	// Iterate matrix and check if every 0 is surrounded by other 0 or 1
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == '0')
			{
				// Can't have a 0 on the first line or the last line
				if (i == 0 || i == last_line)
					return (FALSE);
				// Can't have an open space to the right
				if (array[i][j + 1] != '1' && array[i][j + 1] != '0')
					return (FALSE);
				// Can't have an open space to the left
				if (array[i][j - 1] != '1' && array[i][j - 1] != '0')
					return (FALSE);
				// Can't have an open space above
				if (ft_strlen(array[i - 1]) < i)
					return (FALSE);
				if (array[i - 1][j] != '1' && array[i - 1][j] != '0')
					return (FALSE);
				// Can't have an open space below
				if (ft_strlen(array[i + 1]) < i)
					return (FALSE);
				if (array[i + 1][j] != '1' && array[i + 1][j] != '0')
					return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	has_invalid_characters(char *map)
{
	while (*map)
	{
		map++;
		if (!*map)
			return (FALSE);
		if (*map == ' ' || *map == '\n')
			continue;
		if (*map == '0' || *map == '1')
			continue;
		if (*map == 'N' || *map == 'S' || *map == 'E' || *map == 'W')
			continue;
		printf("Invalid character:(%c)\n", *map);
		return (TRUE);
	}
	return (FALSE);
}

int has_starting_position(char *map)
{
	while (*map)
	{
		if (*map == 'N' || *map == 'S' || *map == 'E' || *map == 'W')
			return (TRUE);
		map++;
	}
	return (FALSE);
}

int	valid_map_tiles(char *map)
{
	if (has_invalid_characters(map))
	{
		printf("Contains invalid characters\n");
		return(FALSE);
	}
	if (!has_starting_position(map))
	{
		printf("Starting position not present\n");
		return(FALSE);
	}
	if (!surrounded_by_walls(map))
		return(FALSE);
	return(TRUE);
}

int	has_errors(char *map)
{
	int	identifier_size;

	// Check all identifiers
	while(*map != '\0')
	{
		while (*map && *map == '\n')
			map++;
		// Exit the identifiers check when a map starts
		if (*map == '1' || *map == ' ')
			break;
		identifier_size = 0;
		while(map[identifier_size] && map[identifier_size] != ' ')
			identifier_size++;
		if (identifier_size != 1 && identifier_size != 2)
		{
			printf("Idenfier size invalid\n");
			return (TRUE);
		}
		if (identifier_size == 2)
		{
			if (invalid_texture(map))
				return(TRUE);
		}
		if (identifier_size == 1)
		{
			if (invalid_color(map))
			{
				printf("Invalid color\n");
				return(TRUE);
			}
		}
		// Go to the end of the line
		while (*map && *map != '\n')
			map++;
	}
	if (any_identifier_missing())
	{
		printf("At least 1 identifier is missing\n");
		return (TRUE);
	}
	if (!valid_map_tiles(map))
		return (TRUE);
	return (FALSE);
}

int is_valid(char *map_name)
{
	char	*map;
	if (!valid_extension(map_name))
		return (FALSE);
	map = load_map(map, open(map_name, O_RDONLY));
	if (!map)
		return (FALSE);
	if (has_errors(map))
		return (FALSE);
	free(map);
	return(TRUE);
}

int exit_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	exit(1);
}

int	main(int argc, char **argv)
{
	char *map_name;

	map_name = argv[1];
	if (argc < 2)
		exit_error("Please provide a map");
	if(!is_valid(map_name))
		exit_error("Invalid map");
	mlx = mlx_init();
	win = mlx_new_window(mlx, 200, 200, "cub3D");
	mlx_hook(win, BTN_X, NO_EVENT, close_game, NULL);
	mlx_key_hook(win, key_hook, NULL);
	mlx_loop(mlx);
	return (0);
}
