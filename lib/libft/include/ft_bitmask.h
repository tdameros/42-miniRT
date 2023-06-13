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

void	ft_bitmask_free(t_bitmask *bitmask);
void	ft_bitmask_get_position(size_t target, size_t *index,
			int8_t *right_shift);
bool	ft_bitmask_get(t_bitmask bitmask, size_t target);
int		ft_bitmask_init(t_bitmask *bitmask, size_t size);
void	ft_bitmask_set(t_bitmask bitmask, size_t target, bool new_value);

#endif
