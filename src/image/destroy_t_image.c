/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_t_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:39:31 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:39:31 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"

#include "engine.h"
#include "image.h"

void	destroy_t_image(t_window *minirt_window, t_image *image)
{
	if (image->data != NULL)
		mlx_destroy_image(minirt_window->mlx, image->data);
	ft_bzero(image, sizeof(*image));
}
