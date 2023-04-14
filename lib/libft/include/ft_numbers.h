/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 02:43:12 by vfries            #+#    #+#             */
/*   Updated: 2022/12/02 12:33:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NUMBERS_H
# define FT_NUMBERS_H

# include <stddef.h>
# include <sys/types.h>

int			ft_abs(int i);

int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
char		*ft_itoa(int n);

void		ft_swap_double(double *a, double *b);
void		ft_swap_int(int *a, int *b);
void		ft_swap_long(long *a, long *b);
void		ft_swap_size_t(size_t *a, size_t *b);
void		ft_swap_ssize_t(ssize_t *a, ssize_t *b);
void		ft_swap_uint(unsigned int *a, unsigned int *b);

#endif
