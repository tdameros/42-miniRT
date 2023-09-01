/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_ppm_box.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:37:19 by vfries            #+#    #+#             */
/*   Updated: 2023/09/01 18:37:19 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

static void		set_normal_map(const t_color_and_material *color_and_material,
					t_object *object, size_t index, bool is_cap);
static void		set_texture(const t_color_and_material *color_and_material,
					t_object *object, size_t index, bool is_cap);

void	click_ppm_box(t_engine *engine, size_t index)
{
	t_object					*object;
	const t_color_and_material	*color_and_material
		= &engine->gui.color_and_material;
	const bool					is_normal_map
		= color_and_material->changing_normal_map_or_texture == NORMAL_MAP;
	const bool					is_cap
		= color_and_material->texture_being_changed == CAP_TEXTURE;

	object = engine->gui.selected_object.object;
	if (object == NULL)
		return ;
	if (is_normal_map)
		set_normal_map(color_and_material, object, index, is_cap);
	else
		set_texture(color_and_material, object, index, is_cap);
	engine->scene_changed = true;
	redraw_icons(engine, object->material);
}

static void	set_normal_map(const t_color_and_material *color_and_material,
				t_object *object, size_t index, const bool is_cap)
{
	char	**files;

	files = color_and_material->textures_and_normal_maps.normal_maps_files;
	if (is_cap)
	{
		if (set_cap_normals_map(&object->material, files[index]) < 0)
		{
			ft_print_error("Warning: Failed to set cap normal map ");
			ft_print_error(files[index]);
			ft_print_error("\n");
		}
	}
	else
	{
		if (set_outline_normals_map(&object->material, files[index]) < 0)
		{
			ft_print_error("Warning: Failed to set outline normal map ");
			ft_print_error(files[index]);
			ft_print_error("\n");
		}
	}
}

static void	set_texture(const t_color_and_material *color_and_material,
				t_object *object, size_t index, const bool is_cap)
{
	char	**files;

	files = color_and_material->textures_and_normal_maps.textures_files;
	if (is_cap)
	{
		if (set_cap_texture(&object->material, files[index]) < 0)
		{
			ft_print_error("Warning: Failed to set cap texture ");
			ft_print_error(files[index]);
			ft_print_error("\n");
		}
	}
	else
	{
		if (set_outline_texture(&object->material, files[index]) < 0)
		{
			ft_print_error("Warning: Failed to set outline texture ");
			ft_print_error(files[index]);
			ft_print_error("\n");
		}
	}
}
