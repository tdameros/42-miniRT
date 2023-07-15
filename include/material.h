/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:21:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/13 17:21:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "math/vector.h"
# include "ppm.h"

enum e_texture_type
{
	NONE,
	PPM_TEXTURE,
	CHECKER_BOARD,
};

typedef struct s_checker_board
{
	float		width;
	float		height;
	t_vector3f	albedo;
}	t_checkers_pattern;

typedef struct s_texture
{
	enum e_texture_type	type;
	t_ppm_p6			texture_file;
	t_checkers_pattern	checker_board;
	t_ppm_p6			bump_map;
	bool				has_bump_map;

}	t_texture;

typedef struct s_material
{

	t_vector3f	albedo;
	float		reflect;
	float		specular;
	t_texture	texture;
}	t_material;

//	material.c
t_material	material_create(const t_vector3f albedo, \
							const float reflect_intensity, \
							const float specular_intensity);

//	texture.c
t_texture	texture_empty_create(void);
int			set_ppm_texture_in_material(t_material *material,
				const char *filename);
void		set_checker_board_in_material(t_material *material,
				const t_vector2f size,
				const t_vector3f albedo);
void		free_texture_in_material(t_material *material);
#endif
