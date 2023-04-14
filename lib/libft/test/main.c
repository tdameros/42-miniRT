/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:29:14 by vfries            #+#    #+#             */
/*   Updated: 2023/04/09 00:33:44 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_string_test.h"
#include "ft_bitmask_test.h"
#include "hashmap_test.h"
#include "linked_list.h"

int	main(void)
{
	if (ft_join_strs_test() == false)
		ft_putstr("ft_join_strs: KO\n");
	if (ft_hashmap_test() == false)
		ft_putstr("hashmap: KO\n");
	if (ft_bitmask_test() == false)
		ft_putstr("bitmask: KO\n");
	if (ft_doubly_linked_void_ptr_test() == false)
		ft_putstr("linked list void *: KO\n");
	ft_putstr("Tests done\n");
}
