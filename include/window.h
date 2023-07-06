/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:58:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/11 00:58:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
//# define WINDOW_WIDTH 1000
//# define WINDOW_HEIGHT 500
//# define WINDOW_WIDTH 1920
//# define WINDOW_HEIGHT 1080

typedef struct s_window
{
	void	*mlx;
	void	*window;
}	t_window;

#endif
