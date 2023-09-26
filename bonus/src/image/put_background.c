/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:47:35 by vfries            #+#    #+#             */
/*   Updated: 2023/09/24 03:40:36 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	put_background(t_image *destination, const t_image *source)
{
	register const unsigned int	*dest_end
		= destination->address + destination->height * destination->width;
	register unsigned int		*dest_curr;
	register unsigned int		*source_curr;

	source_curr = source->address;
	dest_curr = destination->address;
	while (dest_curr < dest_end)
		*dest_curr++ = *source_curr++;
}
