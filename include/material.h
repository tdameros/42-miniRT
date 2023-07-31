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
	CHECKERBOARD,
	PPM_TEXTURE,
};

typedef struct s_checker_board
{
	t_vector2f	size;
	t_vector3f	albedo;
}	t_checkerboard;

typedef struct s_surface
{
	enum e_texture_type	texture_type;
	t_ppm_p6			texture;
	char				*texture_file;
	t_ppm_p6			bump_map;
	char				*bump_map_file;
	t_checkerboard		checkerboard;
	bool				has_bump_map;

}	t_surface;

typedef struct s_texture
{
	t_surface	cap;
	t_surface	outline;

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
int	set_outline_ppm_normal(t_material *material, const char *filename);
t_texture	create_empty_texture(void);
int			set_outline_ppm_texture(t_material *material,
				const char *filename);
int			set_cap_ppm_texture(t_material * material,
				const char *filename);
void		free_outline_texture(t_material *material);
void		free_cap_texture(t_material *material);
#endif
