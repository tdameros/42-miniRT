#include "struct/t_minirt.h"
#include "struct/t_gui_box.h"

static void	update_gui_hidden_ration(t_gui *gui);
static int	get_y_decal(const t_gui_box *gui_box, const t_gui *gui);
static int	get_x_decal(const t_gui_box *gui_box, const t_gui *gui);

void render_user_interface(t_minirt *minirt)
{
	update_gui_hidden_ration(&minirt->gui);
	if (minirt->gui.hidden_ratio == 1.0)
		return ;
	minirt->gui.gui_boxes.data[0].draw(minirt->gui.gui_boxes.data + 0, minirt,
		0, get_y_decal(minirt->gui.gui_boxes.data + 0, &minirt->gui));
	minirt->gui.gui_boxes.data[1].draw(minirt->gui.gui_boxes.data + 1, minirt,
		get_x_decal(minirt->gui.gui_boxes.data + 1, &minirt->gui), 0);
}

static void	update_gui_hidden_ration(t_gui *gui)
{
	if (gui->is_hidden && gui->hidden_ratio < 1.0)
	{
		gui->hidden_ratio += 0.015;
		if (gui->hidden_ratio > 1.0)
			gui->hidden_ratio = 1.0;
	}
	else if (!gui->is_hidden && gui->hidden_ratio > 0.0)
	{
		gui->hidden_ratio -= 0.015;
		if (gui->hidden_ratio < 0.0)
			gui->hidden_ratio = 0.0;
	}
}

static int	get_y_decal(const t_gui_box *gui_box, const t_gui *gui)
{
	return ((int)-((gui_box->size.height + gui_box->position.y)
		* gui->hidden_ratio));
}

static int	get_x_decal(const t_gui_box *gui_box, const t_gui *gui)
{
	return ((int)((WINDOW_WIDTH - gui_box->position.x)
		* gui->hidden_ratio));
}
