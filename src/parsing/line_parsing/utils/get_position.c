/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:40:51 by vfries            #+#    #+#             */
/*   Updated: 2023/05/07 18:40:51 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:19:25 by vfries            #+#    #+#             */
/*   Updated: 2023/04/21 03:19:29 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "libft.h"

#include "engine.h"

int	get_position(char *position_string, t_vector3f *position_destination)
{
	char	**position_split;

	position_split = ft_split(position_string, ',');
	if (position_split == NULL)
		return (-1);
	if (ft_split_len(position_split) != 3)
	{
		ft_free_split(position_split);
		return (-1);
	}
	position_destination->x = ft_atof(position_split[0]);
	position_destination->y = ft_atof(position_split[1]);
	position_destination->z = ft_atof(position_split[2]);
	ft_free_split(position_split);
	if (errno == ERANGE || errno == EINVAL)
		return (-1);
	return (0);
}
