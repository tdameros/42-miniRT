/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_minirt_folder_as_current_working_direct        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:01:40 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 17:02:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static char	*get_path_to_minirt_folder(const char *path_to_minirt_binary);

int	set_minirt_folder_as_current_working_directory(
				const char *path_to_minirt_binary)
{
	char	*path_to_minirt_folder;

	path_to_minirt_folder = get_path_to_minirt_folder(path_to_minirt_binary);
	if (path_to_minirt_folder == NULL)
		return (-1);
	if (chdir(path_to_minirt_folder) < 0)
	{
		free(path_to_minirt_folder);
		return (-1);
	}
	free(path_to_minirt_folder);
	return (0);
}

static char	*get_path_to_minirt_folder(const char *path_to_minirt_binary)
{
	char	*path_to_executable;
	char	*last_backslash;
	char	*path_to_minirt_folder;

	path_to_executable = realpath(path_to_minirt_binary, NULL);
	if (path_to_executable == NULL)
		return (NULL);
	last_backslash = ft_strrchr(path_to_executable, '/');
	if (last_backslash == NULL)
		path_to_minirt_folder = ft_strdup(path_to_executable);
	else
		path_to_minirt_folder = ft_substr(path_to_executable, 0,
				last_backslash - path_to_executable);
	free(path_to_executable);
	return (path_to_minirt_folder);
}
