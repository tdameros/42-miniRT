/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:41:35 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 16:58:08 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "path.h"

#define EXPECTED_EXECUTION_COMMAND "./miniRT *.rt"

static bool			arguments_are_bad(int argc, const char **argv);
static const char	*get_startup_scene_path(const int argc, const char **argv);

int	main(const int argc, const char **argv)
{
	t_engine	engine;
	const char	*start_up_scene = get_startup_scene_path(argc, argv);

	if (arguments_are_bad(argc, argv))
		return (1);
	if (init_engine(&engine, start_up_scene, argv[0]) < 0)
	{
		ft_putstr_fd("Error: Failed to init miniRT\n", STDERR_FILENO);
		close_engine(&engine);
		return (2);
	}
	mlx_loop(engine.window.mlx);
}

static bool	arguments_are_bad(const int argc, const char **argv)
{
	char	*file_extension;

	if (argc == 1)
		return (false);
	if (argc > 2)
	{
		ft_putstr_fd("Unexpected argument count, expected:\n\t"
			EXPECTED_EXECUTION_COMMAND"\n", STDERR_FILENO);
		return (true);
	}
	file_extension = ft_strrstr(argv[1], ".rt");
	if (file_extension == NULL || file_extension[3] != '\0')
	{
		ft_putstr_fd("Unexpected file extension, expected:\n\t"
			EXPECTED_EXECUTION_COMMAND"\n", STDERR_FILENO);
		return (true);
	}
	return (false);
}

static const char	*get_startup_scene_path(const int argc, const char **argv)
{
	if (argc == 1)
		return (DEFAULT_STARTUP_SCENE_PATH);
	else
		return (argv[1]);
}
