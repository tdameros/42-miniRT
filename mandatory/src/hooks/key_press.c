/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:37:00 by vfries            #+#    #+#             */
/*   Updated: 2023/09/25 22:34:35 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "events.h"
#include "engine.h"
#include "hooks.h"
#include "export.h"

int	key_press_handler(int key_code, t_engine *engine)
{
	if (key_code == KEY_ESC)
		close_engine(engine);
	return (0);
}
