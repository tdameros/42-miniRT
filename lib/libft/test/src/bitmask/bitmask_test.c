/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmask_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:50:43 by vfries            #+#    #+#             */
/*   Updated: 2023/02/27 18:17:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_bitmask.h"
#include "ft_io.h"

#define SIZE 104
#define STR_SIZE 100000

static int	all_bits_are_zero(t_bitmask bitmask);
static int	set_all_bits_to_one(t_bitmask bitmask);
static int	set_all_bits_to_zero(t_bitmask bitmask);
static int	real_application_test(void);

bool	ft_bitmask_test(void)
{
	t_bitmask		bitmask;

	if (ft_bitmask_init(&bitmask, SIZE) < 0)
		return (ft_putstr_fd("Bitmask: malloc failed\n", STDERR_FILENO),
			ft_bitmask_free(&bitmask), false);
	if (all_bits_are_zero(bitmask) < 0)
		return (ft_putstr_fd("Bitmask: all_bits_are_zero()\n", STDERR_FILENO),
			ft_bitmask_free(&bitmask), false);
	if (set_all_bits_to_one(bitmask) < 0)
		return (ft_putstr_fd("Bitmask: set_all_bits_to_one()\n", STDERR_FILENO),
			ft_bitmask_free(&bitmask), false);
	if (set_all_bits_to_zero(bitmask) < 0)
		return (ft_putstr_fd("Bitmask: set_all_bits_to_zero()\n", STDERR_FILENO),
			ft_bitmask_free(&bitmask), false);
	if (real_application_test())
		return (ft_putstr_fd("Bitmask: real_application_test()\n",
				STDERR_FILENO), ft_bitmask_free(&bitmask), false);
	ft_bitmask_free(&bitmask);
	return (true);
}

static int	all_bits_are_zero(t_bitmask bitmask)
{
	size_t	i;

	i = 0;
	while (i < SIZE)
	{
		if (ft_bitmask_get(bitmask, i) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	set_all_bits_to_one(t_bitmask bitmask)
{
	size_t	i;

	i = 0;
	while (i < SIZE)
	{
		ft_bitmask_set(bitmask, i, 1);
		if (ft_bitmask_get(bitmask, i) != 1)
			return (-1);
		i++;
	}
	return (0);
}

static int	set_all_bits_to_zero(t_bitmask bitmask)
{
	size_t	i;

	i = 0;
	while (i < SIZE)
	{
		ft_bitmask_set(bitmask, i, 0);
		if (ft_bitmask_get(bitmask, i) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	real_application_test(void)
{
	t_bitmask	bitmask;
	char		str[STR_SIZE];
	int			i;

	if (ft_bitmask_init(&bitmask, STR_SIZE))
		return (ft_putstr_fd("Malloc failed\n", STDERR_FILENO), -1);
	i = 0;
	while (i < STR_SIZE)
	{
		str[i] = rand() % 2;
		ft_bitmask_set(bitmask, i, str[i]);
		i++;
	}
	i = 0;
	while (i < STR_SIZE)
	{
		if (ft_bitmask_get(bitmask, i) != str[i])
			return (ft_bitmask_free(&bitmask), -1);
		i++;
	}
	ft_bitmask_free(&bitmask);
	return (0);
}
