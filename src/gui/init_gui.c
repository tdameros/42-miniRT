#include <stdlib.h>
#include <errno.h>

#include "engine.h"
#include "gui/box.h"
#include "gui/main_gui_box.h"
#include "window.h"
#include "libft.h"
#include "gui/object_modification_box.h"
#include "gui/object_list_box.h"

int init_gui(t_engine *engine)
{
	engine->gui.draw_gui_image = &put_image_to_image_unsafe;
	engine->gui.gui_boxes.size = 3;
	engine->gui.gui_boxes.data = malloc(sizeof(*engine->gui.gui_boxes.data)
			* engine->gui.gui_boxes.size);
	if (engine->gui.gui_boxes.data == NULL)
		return (-1);
	engine->gui.object_modification_amount = 0.1f;
	engine->gui.object_rotation_degrees = 10.0f;
	engine->gui.fps.fps_count = ft_itoa(0); // TODO secure me
	engine->gui.fps.last_update = ft_get_current_time();
	engine->gui.material_to_assign_to_new_objects = material_create(
			(t_color){0.f, 0.f, 1.f}, 0.f, 0.f);
	if (init_main_gui_box(engine,
			engine->gui.gui_boxes.data) < 0)
	{
		free(engine->gui.gui_boxes.data);
		return (-1);
	}
	if (init_object_modification_gui_box(engine,
			engine->gui.gui_boxes.data + 1, engine->gui.gui_boxes.data) < 0)
	{
		// TODO free first gui box
		free(engine->gui.gui_boxes.data);
		return (-1);
	}
	if (init_object_list_box(engine, engine->gui.gui_boxes.data + 2,
			engine->gui.gui_boxes.data, engine->gui.gui_boxes.data + 1) < 0)
	{
		// TODO free first and second gui box
		free(engine->gui.gui_boxes.data);
		return (-1);
	}
	return (0);
}
