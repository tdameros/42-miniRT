/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:41:35 by vfries            #+#    #+#             */
/*   Updated: 2023/04/12 20:46:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"

#include "engine.h"
#include "font/ttf_parser.h"

#define EXPECTED_EXECUTION_COMMAND "./miniRT *.rt"

static bool	arguments_are_bad(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_engine	minirt;


	if (arguments_are_bad(argc, argv))
		return (1);
	if (init_engine(&minirt, argv[1]) < 0)
	{
		ft_putstr_fd("Error: Failed to init miniRT\n", STDERR_FILENO);
		return (2);
	}
	mlx_loop(minirt.window.mlx);
}

static bool	arguments_are_bad(int argc, char **argv)
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