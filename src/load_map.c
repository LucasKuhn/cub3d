/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:43:12 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/25 14:55:44 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static int	get_file_size(char *map_name)
{
	int		fd;
	int		size;
	char	buffer[1];

	size = 0;
	fd = open(map_name, O_RDONLY);
	while (read(fd, buffer, 1))
		size++;
	close(fd);
	return (size);
}

static int	has_line_break_in_map_area(char *file)
{
	int	i;

	i = 0;
	while (file[i] && file[i + 1])
	{
		while (file[i] != '\n' && file[i])
			i++;
		if (file[i] && file[i + 1] && (file[i + 1] == '1' || file[i + 1] == ' '))
			break ;
		i++;
	}
	while (file[i] && file[i + 1])
	{
		while (file[i] && file[i] != '\n')
			i++;
		if (file[i] && file[i + 1] && file[i + 1] == '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	load_map(t_game *game, char *map_name)
{
	char	*file;
	char	**map;
	int		fd;
	int		file_size;

	file_size = get_file_size(map_name);
	fd = open(map_name, O_RDONLY);
	if (fd <= 0)
		exit_error("Error opening map file");
	file = malloc(sizeof(char) * (file_size + 1));
	read(fd, file, file_size);
	file[file_size] = '\0';
	close(fd);
	if (has_line_break_in_map_area(file))
	{
		free(file);
		exit_error("Map contain empty line breaks");
	}
	map = ft_split(file, '\n');
	free(file);
	game->map = map;
	game->map_original = map;
}
