/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:25:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/08/06 22:25:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include <stdbool.h>

# include "math/vector.h"

bool	point_is_in_triangle(t_vector3f point, t_vector3f vertex_a,
			t_vector3f vertex_b, t_vector3f vertex_c);

#endif