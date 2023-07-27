/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_release.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 04:26:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/01 04:26:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "events.h"
#include "hooks.h"
#include "mlx.h"

int	button_release_handler(int button, int x, int y, t_engine *engine)
{
	(void)button;
	(void)x;
	(void)y;
	(void)engine;
	return (0);
}
