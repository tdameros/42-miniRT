/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmask.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:16:42 by vfries            #+#    #+#             */
/*   Updated: 2023/02/25 13:51:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BITMASK_H
# define FT_BITMASK_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

typedef struct s_bitmask
{
	uint8_t	*arr;
}	t_bitmask;

//	bitmask_free.c
void	ft_bitmask_free(t_bitmask *bitmask);

//	bitmask_get.c
bool	ft_bitmask_get(t_bitmask bitmask, size_t target);

//	bitmask_get_position.c
void	ft_bitmask_get_position(size_t target, size_t *index,
			int8_t *right_shift);

//	bitmask_init.c
int		ft_bitmask_init(t_bitmask *bitmask, size_t size);

//	bitmask_set.c
void	ft_bitmask_set(t_bitmask bitmask, size_t target, bool new_value);

#endif
