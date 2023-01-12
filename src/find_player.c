#include "./include/cub3d.h"

t_vector	find_player(t_game *game)
{
	t_vector	player;
	int			i;
	int			j;
	char		**map;

	map = game->map;
	// skip texture lines
	while (*map[0] != ' ' && *map[0] != '1')
		map++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
				game->player_direction = 90;
			if (map[i][j] == 'E')
				game->player_direction = 0;
			if (map[i][j] == 'S')
				game->player_direction = 270;
			if (map[i][j] == 'W')
				game->player_direction = 180;
			if (ft_strchr("NSEW", map[i][j]))
			{
				game->direction_in_radian = game->player_direction * (M_PI
						/ 180.0);
				player.x = j * MOVING_SPEED;
				player.y = i * MOVING_SPEED;
				return (player);
			}
			j++;
		}
		i++;
	}
	return (player);
}
