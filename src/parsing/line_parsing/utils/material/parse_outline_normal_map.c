/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outline_normal_map.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:05:38 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:05:39 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

void	parse_outline_normal_map(t_object *object, char *file)
{
	if (set_outline_normals_map(&object->material, file) < 0)
	{
		ft_print_error("Failed to set outline normal map during parsing ");
		ft_print_error(file);
		ft_print_error("\n");
	}
}
