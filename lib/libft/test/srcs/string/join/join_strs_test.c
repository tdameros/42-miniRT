/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_strs_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:20:15 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:12:41 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdbool.h>
#include <stdlib.h>

#define EXPECTED "test||42||cool||42||wow||42||Not a string"

bool	ft_join_strs_test(void)
{
	char	**strs;
	char	*str;

	strs = malloc(sizeof(char *) * 5);
	strs[0] = ft_strdup("test");
	strs[1] = ft_strdup("cool");
	strs[2] = ft_strdup("wow");
	strs[3] = ft_strdup("Not a string");
	strs[4] = NULL;
	str = ft_join_strs(strs, "||42||");
	if (ft_strlen(str) != ft_strlen(EXPECTED))
	{
		ft_free_split(strs);
		free(str);
		return (false);
	}
	if (ft_strncmp(str, EXPECTED, ft_strlen(str)))
	{
		ft_free_split(strs);
		free(str);
		return (false);
	}
	ft_free_split(strs);
	free(str);
	return (true);
}
