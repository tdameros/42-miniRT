/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_in_strs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 04:26:23 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/08 04:26:24 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ft_string.h"

bool	ft_str_is_in_strs(char *str, char **strs)
{
	if (str == NULL || strs == NULL)
		return (false);
	while (*strs != NULL)
	{
		if (ft_strcmp(str, *strs) == 0)
			return (true);
		strs++;
	}
	return (false);
}
