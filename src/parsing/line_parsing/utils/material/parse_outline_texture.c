/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outline_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:05:40 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:05:41 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "object.h"

void	parse_outline_texture(t_object *object, char *file)
{
	if (set_outline_texture(&object->material, file) < 0)
	{
		ft_print_error("Failed to set outline texture during parsing ");
		ft_print_error(file);
		ft_print_error("\n");
	}
}
