/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:50:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/05 16:50:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

float	ft_minf(float a, float b)
{
	return ((a <= b) * a + (a < b) * b);
}

float	ft_minf_positive(float a, float b)
{
	return (((a < 0) * (a * (a >= b) + b * (b > a)))
			+ ((b < 0 && a > 0) * (b * (b >= a) + a * (a > b)))
			+ (a > 0 && b > 0) * (a * (a <= b) + b * (b < a)));
}
