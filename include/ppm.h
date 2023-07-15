/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:42:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/15 10:42:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPM_H
# define PPM_H

# include "math/vector.h"

typedef struct s_ppm_p6
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	size;
	t_vector3f		*pixels;
}	t_ppm_p6;

int	initialize_ppm_p6_file(t_ppm_p6 *ppm, const char *filename);

#endif