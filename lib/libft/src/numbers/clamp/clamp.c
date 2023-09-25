/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:58:14 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:58:14 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_clamp(const int nb, const int min, const int max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}
