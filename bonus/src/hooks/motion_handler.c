/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:04:50 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/24 03:04:51 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	motion_handler(int x, int y, t_engine *engine)
{
	engine->mouse_position.x = x;
	engine->mouse_position.y = y;
	return (0);
}
