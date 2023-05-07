/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_object.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:42:20 by vfries            #+#    #+#             */
/*   Updated: 2023/05/07 18:42:20 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_OBJECT_H
# define T_OBJECT_H

# include <stddef.h>

# include "struct/t_color.h"

enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
};

typedef struct s_object
{
	enum e_object_type	type;
	t_vector3	position;
	t_color 	color;
	double		diameter;
	double		height;
	t_vector3	normal;
}	t_object;

typedef struct s_objects
{
	t_object			*data;
	size_t				length;
	size_t				size;
}	t_objects;

#endif //T_OBJECT_H
