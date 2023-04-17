/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_start_up.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:45:42 by vfries            #+#    #+#             */
/*   Updated: 2023/04/15 10:45:43 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_START_UP_H
# define MINIRT_START_UP_H

# include "struct/t_minirt.h"

int		init_minirt(t_minirt *minirt, const char *start_up_scene);

#endif //MINIRT_START_UP_H
