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
	CHECKERBOARD,
	PPM_TEXTURE,
};

typedef struct s_checker_board
{
	t_vector2f	size;
	t_vector3f	albedo;
}	t_checkerboard;

typedef struct s_texture
{
	enum e_texture_type	outline_type;
	enum e_texture_type	cap_type;
	t_ppm_p6			outline_texture;
	t_ppm_p6			cap_texture;
	t_ppm_p6			bump_map;
	t_checkerboard		outline_checkerboard;
	t_checkerboard		cap_checkerboard;
	bool				has_bump_map;

}	t_texture;

typedef struct s_material
{

	t_vector3f	albedo;
	float		reflect;
	float		specular;
	t_texture	texture;
}	t_material;

//	checker_board.c
void		set_outline_checkerboard(t_material *material,
				const t_vector2f size,
				const t_vector3f albedo);
void		set_cap_checkerboard(t_material *material,
				const t_vector2f size,
				const t_vector3f albedo);

//	material.c
t_material	material_create(const t_vector3f albedo, \
							const float reflect_intensity, \
							const float specular_intensity);

//	texture.c
t_texture	create_empty_texture(void);
int			set_outline_ppm_texture(t_material *material,
				const char *filename);
int			set_cap_ppm_texture(t_material * material,
				const char *filename);
void		free_outline_texture(t_material *material);
void		free_cap_texture(t_material *material);
#endif
