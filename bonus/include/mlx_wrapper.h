/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:35:28 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 03:35:29 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_WRAPPER_H
# define MLX_WRAPPER_H

# include "engine.h"

void		get_screen_size(t_engine *engine);
int			mouse_move(t_engine *engine, t_vector2i position);
int			mouse_hide(t_engine *engine);
int			mouse_show(t_engine *engine);
void		put_image(t_engine *engine, t_image *image, t_vector2i position);

#endif
