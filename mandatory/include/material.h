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
	t_checkerboard		checkerboard;
	t_ppm_p6			normals_map;
	char				*normals_map_file;
	bool				has_normals_map;

}	t_surface;

typedef struct s_textures
{
	t_surface	cap;
	t_surface	outline;
}	t_textures;

typedef struct s_material
{
	t_vector3f	albedo;
	float		reflection;
	float		specular;
	t_textures	textures;
}	t_material;

//	checkerboard.c
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
void		material_free(t_material *material);
int			material_deep_copy(t_material *dst, const t_material *src);

//	normals_map.c
int			set_outline_normals_map(t_material *material, const char *filename);
int			set_cap_normals_map(t_material *material, const char *filename);
void		free_outline_normals_map(t_material *material);
void		free_cap_normals_map(t_material *material);

//	textures.c
t_textures	create_empty_texture(void);
int			set_outline_texture(t_material *material, const char *filename);
int			set_cap_texture(t_material *material, const char *filename);
void		free_outline_texture(t_material *material);
void		free_cap_texture(t_material *material);

#endif
