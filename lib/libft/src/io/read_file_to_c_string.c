/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_to_c_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 01:03:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/29 01:03:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_io.h"

char	*ft_read_file_to_c_string(char *file_name)
{
	char		*result;
	t_string	string;

	string = ft_read_file(file_name);
	result = ft_t_string_to_c_string(&string);
	free(string.data);
	return (result);
}
