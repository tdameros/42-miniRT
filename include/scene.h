/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:40:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/21 17:05:24 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"

# include "object.h"
# include "light.h"
# include "vectors.h"

typedef struct s_scene
{
	t_lights					lights;
	t_light						ambient_light;
	t_vector3f					sky_color;
	t_objects					objects;
	t_vectors_int				plane_indexes;
	struct s_objects_bvh_node	*bvh_tree;
	bool						render_shadows;
}	t_scene;

#endif
