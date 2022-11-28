/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:07:19 by lalex-ku          #+#    #+#             */
/*   Updated: 2022/11/24 18:04:30 by lalex-ku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h> // MiniLibX
# include <stdlib.h>
# include <stdio.h> // printf
# include "libft/libft.h" // libft
# include <fcntl.h> // open

# define KEY_ESC 65307
# define BTN_X 17
# define NO_EVENT 0L
# define TRUE 1
# define FALSE 0

typedef enum e_identifiers
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
}			t_identifiers;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			*map_name;
	char			**map;
}	t_game;

#endif
