/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_string_to_c_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:58:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/29 00:58:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_string.h"
#include "ft_mem.h"

char	*ft_t_string_to_c_string(t_string *string)
{
	char	*result;

	if (string->data == NULL)
		return (NULL);
	result = malloc(string->len + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, string->data, string->len);
	result[string->len] = '\0';
	return (result);
}
