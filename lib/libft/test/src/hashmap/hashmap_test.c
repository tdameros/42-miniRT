/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:46:02 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 17:18:12 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include "ft_string.h"
#include <stdlib.h>
#include <stdbool.h>

bool	ft_hashmap_test(void)
{
	t_hashmap	map;
	bool		ret;

	map = ft_hm_init();
	ft_hm_add_elem(map, "test1", ft_strdup("1"), &free);
	ret = ft_strcmp(ft_hm_get_content(map, "test1"), "2") != 0;
	ft_hm_add_elem(map, "test1", ft_strdup("2"), &free);
	if (ft_strcmp(ft_hm_get_content(map, "test1"), "2") != 0)
		ret = true;
	ft_hm_add_elem(map, "test1", ft_strdup("1"), &free);
	if (ft_strcmp(ft_hm_get_content(map, "test1"), "1") != 0)
		ret = true;
	ft_hm_add_elem(map, "test2", ft_strdup("2"), &free);
	if (ft_strcmp(ft_hm_get_content(map, "test2"), "2") != 0)
		ret = true;
	ft_hm_add_elem(map, "test3", ft_strdup("3"), &free);
	if (ft_strcmp(ft_hm_get_content(map, "test3"), "3") != 0)
		ret = true;
	if (ft_hm_get_content(map, "Doesn't exist") != NULL)
		ret = true;
	if (ft_hm_get_elem(map, "Doesn't exist") != NULL)
		ret = true;
	ft_hm_clear(&map, &free);
	return (ret);
}
