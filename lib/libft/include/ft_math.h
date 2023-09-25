/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:19:11 by vfries            #+#    #+#             */
/*   Updated: 2022/12/10 19:19:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <stdint.h>

//	sum/sum_int_arr.c
int64_t		ft_sum_int_arr(const int *arr, size_t size);

//	sum/sum_uint8_arr.c
uint64_t	ft_sum_uint8_arr(const uint8_t *arr, size_t size);

//	angle_to_theta.c
float		ft_angle_to_theta(float angle);

#endif