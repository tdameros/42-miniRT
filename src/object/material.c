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

#include <stdbool.h>

#include "object.h"

t_material	material_create(t_vector3f albedo, float roughness, float metallic)
{
	t_material	material;

	material.albedo = albedo;
	material.roughness = roughness;
	material.reflect = 0;
	material.specular = 0;
	material.is_checked_pattern = false;
	(void) metallic;
	return (material);
}
