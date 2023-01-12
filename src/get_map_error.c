#include "./include/cub3d.h"

// TODO: THIS IS TRASH! NOT OK! PLEASE FIX ME!
int		found_NO = FALSE;
int		found_SO = FALSE;
int		found_WE = FALSE;
int		found_EA = FALSE;
int		found_F = FALSE;
int		found_C = FALSE;

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

int	is_map_start(char *map_line)
{
	return (map_line[0] == '1' || map_line[0] == ' ');
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

char	*get_identifier(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return ("NO");
	if (ft_strncmp(line, "SO ", 3) == 0)
		return ("SO");
	if (ft_strncmp(line, "WE ", 3) == 0)
		return ("WE");
	if (ft_strncmp(line, "EA ", 3) == 0)
		return ("EA");
	if (ft_strncmp(line, "F ", 2) == 0)
		return ("F");
	if (ft_strncmp(line, "C ", 2) == 0)
		return ("C");
	return (NULL);
}

int	has_all_identifiers(char **map)
{
	static int	NO;
	static int	SO;
	static int	WE;
	static int	EA;
	static int	F;
	static int	C;
	char		*identifier;

	while (*map)
	{
		if (*map[0] == '1' || *map[0] == ' ')
			break ;
		identifier = get_identifier(*map);
		if (ft_strncmp(identifier, "NO", 2) == 0)
			NO = TRUE;
		if (ft_strncmp(identifier, "SO", 2) == 0)
			SO = TRUE;
		if (ft_strncmp(identifier, "WE", 2) == 0)
			WE = TRUE;
		if (ft_strncmp(identifier, "EA", 2) == 0)
			EA = TRUE;
		if (ft_strncmp(identifier, "F", 2) == 0)
			F = TRUE;
		if (ft_strncmp(identifier, "C", 2) == 0)
			C = TRUE;
		map++;
	}
	return (NO && SO && WE && EA && F && C);
}

int	has_starting_position(char **map)
{
	int	i;

	while (*map)
	{
		i = 0;
		while ((*map)[i])
		{
			if (ft_strchr("NSEW", (*map)[i]) != NULL)
				return (TRUE);
			i++;
		}
		map++;
	}
	return (FALSE);
}

int	has_invalid_characters(char **map)
{
	int	i;

	while (*map)
	{
		i = 0;
		while ((*map)[i])
		{
			if (ft_strchr("1NWES0 ", (*map)[i]) == NULL)
				return (TRUE);
			i++;
		}
		map++;
	}
	return (FALSE);
}

int	surrounded_by_walls(char **map)
{
	int	i;
	int	j;
	int	last_line;

	// Replace player for 0
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]) != NULL)
				map[i][j] = '0';
			j++;
		}
		i++;
	}
	// Turn map into matrix
	last_line = ft_arrlen(map) - 1;
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

char	*get_map_error(char **map)
{
	char		*identifier;
	static int	identifiers_count;
	char		**identifier_found;

	if (!has_all_identifiers(map))
		return ("At least 1 identifier is missing");
	while (*map && !is_map_start(*map))
	{
		identifier = get_identifier(*map);
		if (!identifier)
			return ("Invalid identifier");
		identifiers_count++;
		if (ft_strlen(identifier) == 2 && invalid_texture(*map))
			return ("Invalid texture");
		if (ft_strlen(identifier) == 1 && invalid_color(*map))
			return ("Invalid color");
		if (identifiers_count > 6)
			return ("Too many identifiers");
		map++;
	}
	if (!has_starting_position(map))
		return ("Starting position not present");
	if (has_invalid_characters(map))
		return ("Contains invalid characters");
	if (!surrounded_by_walls(map))
		return ("Not surrounded by walls");
	return (NULL);
}
