/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ambient_light.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:41:57 by vfries            #+#    #+#             */
/*   Updated: 2023/05/07 18:42:11 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_AMBIENT_LIGHT_H
# define T_AMBIENT_LIGHT_H

# include "colors.h"

typedef struct s_ambient_light
{
	float	lighting_ratio;
	t_color	color;
}	t_ambient_light;

#endif //T_AMBIENT_LIGHT_H
