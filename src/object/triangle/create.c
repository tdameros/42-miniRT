/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:38:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/09 00:38:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

t_object	triangle_create(const t_vector3f vertex_a, const t_vector3f vertex_b,
							const t_vector3f vertex_c, const t_vector3f normal, const t_material material)
{
	t_object	triangle;

	triangle.type = TRIANGLE;
	triangle.vertex_a = vertex_a;
	triangle.vertex_b = vertex_b;
	triangle.vertex_c = vertex_c;
	triangle.axis = normal;
	triangle.material = material;
	triangle.name = ft_strdup("Triangle");
	return (triangle);
}
