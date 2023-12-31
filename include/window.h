/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:58:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/20 20:02:05 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

//# define WINDOW_WIDTH 1280
//# define WINDOW_HEIGHT 720
//# define WINDOW_WIDTH 1920
//# define WINDOW_HEIGHT 1080
//# define WINDOW_WIDTH 2560
//# define WINDOW_HEIGHT 1440
//# define WINDOW_WIDTH 3840
//# define WINDOW_HEIGHT 2160

//# define WINDOW_WIDTH 1380
//# define WINDOW_HEIGHT 820
//# define WINDOW_WIDTH 2460
//# define WINDOW_HEIGHT 1340

# include "math/vector.h"

typedef struct s_window
{
	void		*mlx;
	void		*window;
	t_vector2i	size;
	bool		is_focused;
}	t_window;

# ifdef __APPLE__

extern void	get_screen_size_macos(int *x, int *y);
# endif

#endif
