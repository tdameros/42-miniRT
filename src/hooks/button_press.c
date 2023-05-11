/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:55:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/03 17:55:18 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "engine.h"
#include "gui/box.h"
#include "events.h"

int	button_press_handler(int button, int x, int y, t_engine *minirt)
{
	t_gui_box	*clicked_gui_box;

	ft_printf("button_code == %d\n\n", button);
	if (button != BUTTON_LEFT)
		return (0);
	clicked_gui_box = get_clicked_gui_box(minirt->gui.gui_boxes, &x, &y);
	if (clicked_gui_box != NULL && clicked_gui_box->on_click != NULL)
		clicked_gui_box->on_click(clicked_gui_box, minirt, y, x);
	return (0);
}
