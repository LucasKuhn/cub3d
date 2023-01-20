/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:07:19 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/20 16:52:44 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h" // libft
# include <fcntl.h>       // open
# include <math.h>        // math
# include <mlx.h>         // MiniLibX
# include <stdio.h>       // printf
# include <stdlib.h>

// configurables
# define WIDTH 1080
# define HEIGHT 560
# define WALL_HEIGHT 15
# define TURNING_SPEED 10
# define MOVING_SPEED 4
# define FOV 1.0471975512

# define RED 0xFF0000
# define GREEN 0x00FF00
# define YELLOW 0xFFFF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define KEY_ESC 65307

# define BTN_X 17
# define NO_EVENT 0L

# define TRUE 1
# define FALSE 0

# define ONE_RAD 0.0174533

typedef enum e_identifiers
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
}				t_identifiers;

typedef struct s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct s_image
{
	void		*ptr;
	char		*pixels;
	t_vector	size;
	int			bits;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_textures
{
	t_image		north;
	t_image		south;
	t_image		west;
	t_image		east;
	t_image		frame;
	t_image		player;
	t_image		cube;
}				t_textures;

typedef struct s_ray
{
	double		x;
	double		y;
	double		size;
	t_image		texture;
	int			texture_offset_x;
	double		texture_offset_y;
	double		column_height;
	int			vertical_hit;
}				t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**map_original;
	int			floor[3];
	int			ceiling[3];
	t_vector	player;
	int			player_direction;
	double		direction_in_radian;
	t_textures	textures;
	t_ray		*rays;
}				t_game;

// Map control
void			draw_minimap(t_game *game);
void			move_player(int keycode, t_game *game);
void			draw_3d_view(t_game *game);
void			load_map(t_game *game, char *map_name);
void			set_player(t_game *game);
int				valid_extension(char *map_name);

// Error checking
char			*get_map_error(char **map);
int				surrounded_by_walls(char **map);
int				has_all_textures(char **map);
int				has_all_colors(char **map);
int				has_starting_position(char **map);
int				has_invalid_characters(char **map);
char			*get_identifier(char *line);
void			exit_map_error(t_game *game, char *map_error);
void			exit_error(char *str);

// Utils
char			*ft_strndup(char *str, int n);
void			free_matrix(char **ptr);
size_t			ft_arrlen(char **arr);
int				is_map_start(char *map_line);

// Keycode helpers
int				is_movement(int keycode);
int				is_direction(int keycode);

// Movement utils
void			change_direction(int keycode, t_game *game);
void			move_player(int keycode, t_game *game);
int				can_move_player(int keycode, t_game *game);

// Main render screen function
void			render_screen(t_game *game);
void			draw_column(t_game *game, t_ray ray, int column);

// Raycasting
void			cast_rays(t_game *game);
void			set_ray(t_game *game, t_ray *ray, int vertical_hit, double dir);

// Draw utils
void			draw_player(t_game *game);
void			draw_direction(t_game *game);
void			load_textures(t_game *game);
void			set_colors(t_game *game, char *line);
void			set_texture(t_game *game, char *line);
t_image			new_xpm(t_game *game, char *path);
t_image			new_image(t_game *game, int width, int height);

// Hooks
int				key_hook(int keycode, t_game *game);
int				close_game(t_game *game);
#endif
