/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:45:34 by vfries            #+#    #+#             */
/*   Updated: 2023/04/15 10:45:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_FRAME_H
# define RENDER_FRAME_H

# include "struct/t_minirt.h"

int	render_frame(t_minirt *minirt);

void render_user_interface(t_minirt *minirt);

#endif //RENDER_FRAME_H
