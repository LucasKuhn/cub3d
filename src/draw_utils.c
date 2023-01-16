#include "./include/cub3d.h"

void	draw_direction(t_game *game)
{
	int		x;
	int		y;
	int		i;
	double	d_x;
	double	d_y;

	i = 0;
	d_x = 0;
	d_y = 0;
	while (i < 10)
	{
		d_x += cos(game->direction_in_radian + M_PI);
		d_y += sin(game->direction_in_radian + M_PI);
		mlx_pixel_put(game->mlx, game->win, game->player.x + d_x, game->player.y
				- d_y, 0x00FFFFFF);
		i++;
	}
}

static void	set_colors(t_game *game, char *line)
{
	int		*temp;
	char	**colors;

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

void	set_texture(t_game *game, char *line)
{
	t_image	*temp;

	if (*line == 'N')
		temp = &game->textures.north;
	if (*line == 'W')
		temp = &game->textures.west;
	if (*line == 'S')
		temp = &game->textures.south;
	if (*line == 'E')
		temp = &game->textures.east;
	line += 2;
	while (*line == ' ')
		line++;
	*temp = new_xpm(game, line);
}

t_image	new_image(t_game *game, int width, int height)
{
	t_image	img;

	img.ptr = mlx_new_image(game->mlx, width, height);
	img.pixels = mlx_get_data_addr(img.ptr, &img.bits, &img.line_size,
			&img.endian);
	return (img);
}

void	load_textures(t_game *game)
{
	int i;

	i = 0;
	while (game->map[i][0] != ' ' && game->map[i][0] != '1')
	{
		if (game->map[i][0] == 'C' || game->map[i][0] == 'F')
			set_colors(game, game->map[i]);
		if (game->map[i][0] == 'N' || game->map[i][0] == 'S'
			|| game->map[i][0] == 'W' || game->map[i][0] == 'E')
			set_texture(game, game->map[i]);
		i++;
	}
	while (*(game->map)[0] != ' ' && *(game->map)[0] != '1')
		game->map++;
	game->textures.frame = new_image(game, WIDTH, HEIGHT);
	game->textures.cube = new_xpm(game, "./images/gray10.xpm");
	game->textures.player = new_xpm(game, "./images/yellow3x3.xpm");
}
