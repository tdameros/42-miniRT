/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boxes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:03:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/05/11 00:03:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOXES_H
# define BOXES_H

# include <stddef.h>

typedef struct s_gui_boxes
{
	struct s_gui_box	*data;
	size_t				size;
}	t_gui_boxes;

#endif
