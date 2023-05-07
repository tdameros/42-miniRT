/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:08:33 by tdameros          #+#    #+#             */
/*   Updated: 2022/12/01 23:08:35 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBX_H
# define LIBX_H

# include <stdlib.h>
# include <math.h>

# include "mlx.h"
# include "vector.h"

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

enum e_key_codes
{
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_E = 14,
	KEY_Q = 12,
	KEY_H = 4,
	KEY_SPACE = 49,
	KEY_SLASH = 44,
	KEY_L_SHIFT = 257,
	KEY_R_SHIFT = 258,
	KEY_R_CTRL = 269,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_P = 35,
	KEY_V = 9,
	KEY_C = 8,
	KEY_DOT = 47,
	KEY_S_QUOTE = 39,
	KEY_SEMI_COLON = 41,
};

t_img	*libx_create_image(void *mlx_ptr, int width, int height);
void	libx_put_pixel(t_img *image, t_vector2 coord, t_vector3 color);

#endif
