/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_identifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:38:55 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/18 13:33:46 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

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

int	has_all_colors(char **map)
{
	static int	f;
	static int	c;
	char		*identifier;

	while (*map)
	{
		if (*map[0] == '1' || *map[0] == ' ')
			break ;
		identifier = get_identifier(*map);
		if (identifier == NULL)
			break ;
		if (ft_strncmp(identifier, "F", 2) == 0)
			f = TRUE;
		if (ft_strncmp(identifier, "C", 2) == 0)
			c = TRUE;
		map++;
	}
	return (f && c);
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

int	has_all_textures(char **map)
{
	static int	no;
	static int	so;
	static int	we;
	static int	ea;
	char		*identifier;

	while (*map)
	{
		if (*map[0] == '1' || *map[0] == ' ')
			break ;
		identifier = get_identifier(*map);
		if (identifier == NULL)
			break ;
		if (ft_strncmp(identifier, "NO", 2) == 0)
			no = TRUE;
		if (ft_strncmp(identifier, "SO", 2) == 0)
			so = TRUE;
		if (ft_strncmp(identifier, "WE", 2) == 0)
			we = TRUE;
		if (ft_strncmp(identifier, "EA", 2) == 0)
			ea = TRUE;
		map++;
	}
	return (no && so && we && ea);
}
