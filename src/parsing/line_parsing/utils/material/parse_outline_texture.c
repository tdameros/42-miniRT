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

#define ERROR_MESSAGE "Failed to set outline texture during parsing "

void	parse_outline_texture(t_object *object, char *quoted_file)
{
	const size_t	quoted_file_len = ft_strlen(quoted_file);
	char			*file;

	if (quoted_file_len < 2
		|| quoted_file[0] != '\"' || quoted_file[quoted_file_len - 1] != '\"')
	{
		ft_print_error(ERROR_MESSAGE);
		ft_print_error(file);
		ft_print_error("\n");
		return ;
	}
	quoted_file[quoted_file_len - 1] = '\0';
	file = quoted_file + 1;
	if (set_outline_texture(&object->material, file) < 0)
	{
		ft_print_error(ERROR_MESSAGE);
		ft_print_error(file);
		ft_print_error("\n");
	}
	quoted_file[quoted_file_len - 1] = '\"';
}
