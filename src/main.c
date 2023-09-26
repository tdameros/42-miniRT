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

#include "render_frame.h"
#include "engine.h"
#include "path.h"

#define EXPECTED_EXECUTION_COMMAND "./miniRT *.rt"

static bool			arguments_are_bad(int argc, const char **argv);

int	main(const int argc, const char **argv)
{
	t_engine	engine;

	if (arguments_are_bad(argc, argv))
		return (1);
	if (init_engine(&engine, argv[1], argv[0]) < 0)
	{
		ft_putstr_fd("Error: Failed to init miniRT\n", STDERR_FILENO);
		close_engine(&engine);
		return (2);
	}
	render_frame(&engine);
	mlx_loop(engine.window.mlx);
}

static bool	arguments_are_bad(const int argc, const char **argv)
{
	char	*file_extension;

	if (argc != 2)
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
