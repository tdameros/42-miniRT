/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cap_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:05:34 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:05:35 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

void	parse_cap_texture(t_object *object, char *file)
{
	if (set_cap_texture(&object->material, file) < 0)
	{
		ft_print_error("Failed to set cap texture during parsing ");
		ft_print_error(file);
		ft_print_error("\n");
	}
}
