/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:07:19 by lalex-ku          #+#    #+#             */
/*   Updated: 2023/01/09 21:30:54 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h> // MiniLibX
#include <stdlib.h>
#include <stdio.h>		 // printf
#include "libft/libft.h" // libft
#include <fcntl.h>		 // open
#include <math.h>		 // math

#define RED 0xFF0000
#define GREEN 0x00FF00
#define YELLOW 0xFFFF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF

#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define KEY_ESC 65307

#define BTN_X 17
#define NO_EVENT 0L

#define TRUE 1
#define FALSE 0

#define WIDTH 1080
#define HEIGHT 560

#define TURNING_SPEED 10
#define MOVING_SPEED 5

#define ONE_RAD 0.0174533

#define DEG_TO_RAD(n) (n * (M_PI / 180.0))

typedef enum e_identifiers
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
} t_identifiers;

typedef struct s_vector
{
	int x;
	int y;
} t_vector;

typedef struct s_image
{
	void *ptr;
	char *pixels;
	t_vector size;
	int bits;
	int line_size;
	int endian;
} t_image;

typedef struct s_textures
{
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
	t_image	frame;
	t_image	player;
	t_image	cube;
} t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*map_name;
	char		**map;
	char		**map_original;
	int			floor[3];
	int			ceiling[3];
	t_vector	player;
	int			player_direction;
	double		direction_in_radian;
	t_textures	textures;
} t_game;

typedef struct s_ray
{
	double size;
	t_image texture;
} t_ray;

void draw_minimap(t_game *game);
void move_player(int keycode, t_game *game);
void draw_3d_view(t_game *game);
char *get_map_error(char **map);
t_vector find_player(t_game *game);
char **load_map(char *map_name);
int valid_extension(char *map_name);

// Utils
char *ft_strndup(char *str, int n);
void free_matrix(char **ptr);
size_t ft_arrlen(char **arr);

// Keycode helpers
int is_movement(int keycode);
int is_direction(int keycode);

// Movement utils
void change_direction(int keycode, t_game *game);
void move_player(int keycode, t_game *game);

// Main render screen function
void render_screen(t_game *game);

// Raycasting
void cast_rays(t_game *game, t_ray rays[]);

// Draw utils
void draw_player(t_game *game);
void draw_direction(t_game *game);
void load_map_textures(t_game *game);
t_image new_xpm(t_game *game, char *path);

#endif
