/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:34:45 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/18 13:24:13 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	check_colors(char **colors)
{
	int	i;
	int	num;

	i = 0;
	while (colors[i] != NULL)
		i++;
	if (i > 3)
		return (printf("Too many colors\n"));
	if (i < 2)
		return (printf("Not enough colors\n"));
	i = 0;
	while (colors[i] != NULL)
	{
		num = ft_atoi(colors[i]);
		if (num < 0 || num > 255)
			return (printf("Invalid color '%d'\n", num));
		i++;
	}
	return (0);
}

int	invalid_color(char *map)
{
	char	**colors;
	char	*copy;
	int		info_size;
	int		i;

	i = 0;
	info_size = 0;
	map++;
	while (*map == ' ')
		map++;
	if (!*map)
		return (TRUE);
	while (map[info_size] && map[info_size] != '\n')
		info_size++;
	copy = ft_strndup(map, info_size + 1);
	colors = ft_split(copy, ',');
	if (check_colors(colors) != 0)
	{
		free_matrix(colors);
		free(copy);
		return (TRUE);
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
		return (TRUE);
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

int	identifier_is_valid(char *map)
{
	int		identifier_size;
	char	*identifier;

	identifier = get_identifier(map);
	if (!identifier)
		return (FALSE);
	identifier_size = ft_strlen(identifier);
	if (identifier_size > 2)
		return (FALSE);
	if (identifier_size == 2 && invalid_texture(map))
		return (FALSE);
	if (identifier_size == 1 && invalid_color(map))
		return (FALSE);
	return (TRUE);
}

char	*get_map_error(char **map)
{
	char		*identifier;
	static int	identifiers_count;
	char		**identifier_found;

	if (!has_all_textures(map) || !has_all_colors(map))
		return ("Map is missing identifiers");
	while (*map && !is_map_start(*map))
	{
		if (!identifier_is_valid(*map))
			return ("Invalid identifier");
		identifiers_count++;
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
