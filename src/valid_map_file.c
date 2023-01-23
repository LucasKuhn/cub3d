/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:07:02 by lucferna          #+#    #+#             */
/*   Updated: 2023/01/23 20:48:47 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	valid_map_file(char *map_name)
{
	int		fd;
	char	*extension;

	extension = ft_strrchr(map_name, '.');
	if (!extension || ft_strncmp(extension, ".cub", 4) != 0)
		return (FALSE);
	fd = open(map_name, O_RDONLY);
	if (fd <= 0)
	{
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
