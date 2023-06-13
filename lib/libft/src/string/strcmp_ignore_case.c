/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp_ignore_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:49:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/07 19:49:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_ignore_case(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		while (!ft_isalnum(*s1) && *s1 != '\0')
			s1++;
		while (!ft_isalnum(*s2) && *s2 != '\0')
			s2++;
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return (ft_tolower(*s1) - ft_tolower(*s2));
		if (*s1 != '\0')
			s1++;
		if (*s2 != '\0')
			s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}
