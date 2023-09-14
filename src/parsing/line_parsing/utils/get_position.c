/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:05:56 by vfries            #+#    #+#             */
/*   Updated: 2023/09/03 11:05:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "parsing.h"

int	get_position(const char *position_string, t_vector3f *position_destination)
{
	return (get_vector3f(position_string, position_destination));
}
