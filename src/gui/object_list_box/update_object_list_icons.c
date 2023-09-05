#include "engine.h"
#include "gui/utils.h"
#include "gui/object_list_box.h"

void	update_object_list_icons(t_engine *engine)
{
	t_gui_box	*object_box;
	t_image		*icon_image;
	t_object	*object;
	t_material	material;
	size_t		i;

	i = engine->scene.lights.length;
	while (i--)
	{
		object_box = &((t_gui_box *)engine->gui.light_boxes.data)[i];
		icon_image = object_box_get_icon_image(object_box);
		material = material_create(engine->scene.lights.data[i].color,
				0, 0);
		draw_icon(icon_image, LIGHT, COLOR_TRANSPARENT, material);
	}
	i = engine->scene.objects.length;
	while (i--)
	{
		object_box = &((t_gui_box *)engine->gui.object_boxes.data)[i];
		icon_image = object_box_get_icon_image(object_box);
		object = &engine->scene.objects.data[i];
		material = object->material;
		draw_icon(icon_image, object->type, COLOR_TRANSPARENT, material);
	}
}
