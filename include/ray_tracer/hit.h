/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:10:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/10 16:10:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include <stdlib.h>
# include <stdbool.h>

# include "ray_tracer/ray.h"

typedef struct s_hit {
	bool		hit;
	double		distance;
	size_t		object_index;
	t_vector3	position;
	t_vector3	normal;
}	t_hit;
#endif