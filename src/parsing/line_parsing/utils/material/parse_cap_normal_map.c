/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cap_normal_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:05:32 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:05:33 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

void	parse_cap_normal_map(t_object *object, char *file)
{
	if (set_cap_normals_map(&object->material, file) < 0)
	{
		ft_print_error("Failed to set cap normal map during parsing ");
		ft_print_error(file);
		ft_print_error("\n");
	}
}
