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

#include "mlx.h"

#include "engine.h"
#include "gui/box.h"
#include "gui/utils.h"
#include "events.h"
#include "ray_tracer_gui_api.h"
#include "hooks.h"

static void	update_color_picker_color(t_gui *gui);
static int	placing_object(int button, t_engine *engine);

int	button_press_handler(int button, int x, int y, t_engine *engine)
{
	t_gui_box	*clicked_gui_box;

//	ft_printf("button_code == %d\n\n", button);
	if (button == BUTTON_RIGHT)
	{
		engine->previous_mouse_position = get_mouse_position(engine);
		engine->camera.lock = false;
		mlx_mouse_hide();
	}
	if (button != BUTTON_LEFT && button != SCROLL_DOWN &&  button != SCROLL_UP)
		return (0);

	if (engine->object_being_placed != NULL)
		return (placing_object(button, engine));
	clicked_gui_box = get_clicked_gui_box(engine->gui.gui_boxes, &x, &y);
	if (clicked_gui_box == NULL)
	{
		if (x < 0 || y < 0 || x >= engine->ray_traced_image.width || y >= engine->ray_traced_image.height)
			return (0);
		engine->gui.selected_object = get_clicked_object(engine, x, y);

		// Testing
		char *tmp;
		if (engine->gui.selected_object == NULL)
		{
			ft_printf("Clicked no objects\n\n");
			return (update_object_attributes_modification_box(engine));
		}
		switch (engine->gui.selected_object->type)
		{
			case SPHERE: tmp = "SPHERE"; break;
			case PLANE: tmp = "PLANE"; break;
			case CYLINDER: tmp = "CYLINDER"; break;
			default: tmp = "UNKNOWN: ERROR"; break;
		}
		ft_printf("selected object %s\n\n", tmp);
		//!Testing
		update_color_picker_color(&engine->gui);
		return (update_object_attributes_modification_box(engine));
	}
	if (clicked_gui_box->on_click != NULL)
		clicked_gui_box->on_click(clicked_gui_box, engine, y, x);
	ft_printf("Clicked gui box\n\n");
	return (0);
}

static int	placing_object(int button, t_engine *engine)
{
	if (button == SCROLL_DOWN)
	{
		engine->object_being_placed_distance -= 0.5f;
		return (0);
	}
	else if (button == SCROLL_UP)
	{
		engine->object_being_placed_distance += 0.5f;
		return (0);
	}
	else if (button != BUTTON_LEFT)
		return (0);
	engine->gui.selected_object = engine->object_being_placed;
	engine->object_being_placed = NULL;
	return (update_object_attributes_modification_box(engine));
}

static void	update_color_picker_color(t_gui *gui)
{
	if (gui->selected_object == NULL)
		return ;
	gui->color_picker_base_color_was_changed = true;
	gui->color_picker_base_color = (t_color){
		.x = gui->selected_object->material.albedo.x * 255.f,
		.y = gui->selected_object->material.albedo.y * 255.f,
		.z = gui->selected_object->material.albedo.z * 255.f};
}
