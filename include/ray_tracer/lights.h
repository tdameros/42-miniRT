/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:34:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/19 23:34:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

t_vector3f	calculate_color(t_scene *scene, t_hit ray_hit);
float		calculate_light_intensity(t_scene *scene, t_hit ray_hit);
#endif