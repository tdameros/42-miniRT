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

//	abs/absf.c
float		ft_absf(float i);

//	abs/absi.c
int			ft_absi(int i);

//	clamp/clamp.c
int			ft_clamp(int nb, int min, int max);

//	max/maxf.c
float		ft_maxf(float a, float b);

//	min/minf.c
float		ft_minf(float a, float b);
float		ft_minf_positive(float a, float b);

//	swap/swap_float.c
void		ft_swap_float(float *a, float *b);

//	swap/swap_int.c
void		ft_swap_int(int *a, int *b);

//	swap/swap_long.c
void		ft_swap_long(long *a, long *b);

//	swap/swap_size_t.c
void		ft_swap_size_t(size_t *a, size_t *b);

//	swap/swap_ssize_t.c
void		ft_swap_ssize_t(ssize_t *a, ssize_t *b);

//	swap/swap_uint.c
void		ft_swap_uint(unsigned int *a, unsigned int *b);

//	atof.c
float		ft_atof(const char *string);

//	atoi.c
int			ft_atoi(const char *str);

//	atoll.c
long long	ft_atoll(const char *str);

//	equals.c
bool		ft_is_equalsf(const float a, const float b, const float tolerance);

//	get_smallest_int.c
int			ft_get_smallest_int(int a, int b);

//	itoa.c
char		*ft_itoa(int n);

#endif
