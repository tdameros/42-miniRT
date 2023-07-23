/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 21:50:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/06/16 21:50:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "material.h"

t_material	material_create(const t_vector3f albedo,
							const float reflect_intensity,
							const float specular_intensity)
{
	t_material	material;

	material.texture = create_empty_texture();
	material.albedo = albedo;
	material.reflect = reflect_intensity;
	material.specular = specular_intensity;
	return (material);
}
