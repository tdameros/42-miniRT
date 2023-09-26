/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_deep_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:29:12 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/26 15:51:32 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

int	object_deep_copy(t_object *dst, const t_object *src)
{
	free_object(dst);
	dst->type = src->type;
	dst->position = src->position;
	dst->radius = src->radius;
	dst->height = src->height;
	dst->axis = src->axis;
	dst->axis_degrees = src->axis_degrees;
	dst->cache = src->cache;
	dst->name = ft_strdup(src->name);
	if (dst->name == NULL)
		return (-1);
	return (0);
}
