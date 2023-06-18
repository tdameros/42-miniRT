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

#include "object.h"

t_material	material_create(t_vector3f albedo, float roughness, float metallic)
{
	t_material	material;

	material.albedo = albedo;
	material.roughness = roughness;
	material.metallic = metallic;
	material.emissive_color = vector3f_create(0, 0, 0);
	material.emissive_power = 0;
	material.reflect = 0;
	material.specular = 0;
	return (material);
}
