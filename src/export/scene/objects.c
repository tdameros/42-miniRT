/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:08:49 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 08:08:49 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "object.h"

int	write_sphere(const t_object sphere, int fd)
{
	const ssize_t	return_code = dprintf(fd, "sp\t%f,%f,%f\t%f\t%f,%f,%f\n",
			sphere.position.x,
			sphere.position.y,
			sphere.position.z,
			sphere.radius * 2,
			sphere.material.albedo.x * 255.f,
			sphere.material.albedo.y * 255.f,
			sphere.material.albedo.z * 255.f);

	if (return_code < 0)
		return (-1);
	return (0);
}

int	write_plane(const t_object plane, int fd)
{
	const ssize_t	return_code = dprintf(fd,
			"pl\t%f,%f,%f\t%f,%f,%f\t%f,%f,%f\n",
			plane.position.x,
			plane.position.y,
			plane.position.z,
			plane.axis_degrees.x,
			plane.axis_degrees.y,
			plane.axis_degrees.z,
			plane.material.albedo.x * 255.f,
			plane.material.albedo.y * 255.f,
			plane.material.albedo.z * 255.f);

	if (return_code < 0)
		return (-1);
	return (0);
}

int	write_cylinder(const t_object cylinder, int fd)
{
	const ssize_t	return_code = dprintf(fd, \
								"cy\t%f,%f,%f\t%f,%f,%f\t%f\t%f\t%f,%f,%f\n",
			cylinder.position.x,
			cylinder.position.y,
			cylinder.position.z,
			cylinder.axis_degrees.x,
			cylinder.axis_degrees.y,
			cylinder.axis_degrees.z,
			cylinder.radius * 2,
			cylinder.height,
			cylinder.material.albedo.x * 255.f,
			cylinder.material.albedo.y * 255.f,
			cylinder.material.albedo.z * 255.f);

	if (return_code < 0)
		return (-1);
	return (0);
}

int	write_cone(const t_object cone, int fd)
{
	const ssize_t	return_code = dprintf(fd, \
								"co\t%f,%f,%f\t%f,%f,%f\t%f\t%f\t%f,%f,%f\n",
			cone.position.x,
			cone.position.y,
			cone.position.z,
			cone.axis_degrees.x,
			cone.axis_degrees.y,
			cone.axis_degrees.z,
			cone.radius * 2,
			cone.height,
			cone.material.albedo.x * 255.f,
			cone.material.albedo.y * 255.f,
			cone.material.albedo.z * 255.f);

	if (return_code < 0)
		return (-1);
	return (0);
}

int	write_mesh_object(const t_object mesh, int fd)
{
	const ssize_t	return_code = dprintf(fd, \
			"mesh\t%f,%f,%f\t%f,%f,%f\t%f,%f,%f\t%f,%f,%f\t\"%s\"\n",
			mesh.position.x,
			mesh.position.y,
			mesh.position.z,
			mesh.axis_degrees.x,
			mesh.axis_degrees.y,
			mesh.axis_degrees.z,
			mesh.cache.mesh.scale_vector.x,
			mesh.cache.mesh.scale_vector.y,
			mesh.cache.mesh.scale_vector.z,
			mesh.material.albedo.x * 255.f,
			mesh.material.albedo.y * 255.f,
			mesh.material.albedo.z * 255.f,
			mesh.cache.mesh.obj_file_path);

	if (return_code < 0)
		return (-1);
	return (0);
}
