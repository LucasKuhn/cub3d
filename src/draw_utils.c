#include "./include/cub3d.h"

void draw_direction(t_game *game)
{
	int x;
	int y;

	int i = 0;
	double d_x = 0;
	double d_y = 0;
	while (i < 10)
	{
		d_x += cos(game->direction_in_radian + M_PI);
		d_y += sin(game->direction_in_radian + M_PI);
		mlx_pixel_put(game->mlx, game->win, game->player.x + d_x, game->player.y - d_y, 0x00FFFFFF);
		i++;
	}
}

static void set_colors(t_game *game, char *line)
{
	int *temp;
	char **colors;

	if (*line == 'F')
		temp = game->floor;
	if (*line == 'C')
		temp = game->ceiling;
	while (!ft_isdigit(*line))
		line++;
	colors = ft_split(line, ',');
	temp[0] = ft_atoi(colors[0]);
	temp[1] = ft_atoi(colors[1]);
	temp[2] = ft_atoi(colors[2]);
	free_matrix(colors);
}

/* void set_texture(t_game *game, char *line)
{

} */

void load_map_textures(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i][0] != ' ' && game->map[i][0] != '1')
	{
		if (game->map[i][0] == 'C' || game->map[i][0] == 'F')
			set_colors(game, game->map[i]);
/* 		if (game->map[i][0] == 'N' || game->map[i][0] != 'S' || game->map[i][0] != 'W' || game->map[i][0] != 'E')
			set_texture(game, game->map[i]); */
		i++;
	}
}