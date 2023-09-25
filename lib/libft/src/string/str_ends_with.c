/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ends_with.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:56:45 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:56:46 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

bool	ft_str_ends_with(const char *str, const char *end)
{
	const size_t	str_len = ft_strlen(str);
	const size_t	end_len = ft_strlen(end);

	if (str_len < end_len)
		return (false);
	return (ft_strcmp(str + str_len - end_len, end) == 0);
}
