/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:48:43 by vfries            #+#    #+#             */
/*   Updated: 2023/01/09 01:03:28 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_absi(int i)
{
	return ((i < 0) * (-i) + (i >= 0) * i);
}
