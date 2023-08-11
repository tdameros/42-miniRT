#ifndef OPTIONAL_BOXES_H
# define OPTIONAL_BOXES_H

# include "engine.h"
# include "box.h"

void	init_settings_box(t_engine *engine, t_gui_box *gui_box,
			const t_gui_box *main_gui_box, const t_gui_box *object_list_box);
void	init_antialiasing_toggle_box(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent);
void	init_cam_fov_box(t_engine *engine, t_gui_box *gui_box, int *y,
			t_gui_box *parent);
void	init_max_resolution_reduction_box(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent);
void	init_min_resolution_reduction_box(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent);
void	init_reset_camera_peaking_box(t_engine *engine, t_gui_box *gui_box,
			int *y, t_gui_box *parent);

void	add_button_box(t_engine *engine, t_gui_box *gui_box, int *y,
			t_gui_box *parent);
void	add_plus_minus_box(t_engine *engine, t_gui_box *gui_box, int *y,
			t_gui_box *parent);

#endif //OPTIONAL_BOXES_H
