/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:07:19 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/12/02 17:33:20 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h> // MiniLibX
# include <stdlib.h>
# include <stdio.h> // printf
# include "libft/libft.h" // libft
# include <fcntl.h> // open
# include <math.h> // math

# define RED 0xFF0000
# define GREEN 0x00FF00
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

# define WIDTH 1080
# define HEIGHT 560

# define TURNING_SPEED 10
# define MOVING_SPEED 5

# define ONE_RAD 0.0174533

#define DEG_TO_RAD( n ) ( n * (M_PI/180.0) )

typedef enum e_identifiers
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
}			t_identifiers;

typedef struct s_vector {
	int	x;
	int	y;
}				t_vector;

typedef struct s_image {
	void		*ptr;
	char		*pixels;
	t_vector	size;
	int			bits;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			*map_name;
	char			**map;
	t_vector		player;
	int				player_direction;
	double			direction_in_radian;
	t_image			ground;
	t_image			ceiling;
}				t_game;

void	draw_minimap(t_game *game);

#endif
