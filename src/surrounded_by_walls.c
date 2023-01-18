#include "./include/cub3d.h"

void remove_player(char **map)
{
	int i;
	int j;

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

}

int	surrounded_by_walls(char **map)
{
	int	i;
	int	j;
	int	last_line;

	remove_player(map);
	last_line = ft_arrlen(map) - 1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
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
	return (TRUE);
}
