#include <math.h>

#include "gui/box.h"
#include "gui/UI.h"
#include "gui/main_gui_box.h"
#include "font/render.h"
#include "events.h"
#include "export.h"

#define SIZE_OF_BASE_IMAGE 512.f
#define RATIO_OF_ICON_TO_BOX 0.9f

static void	export_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data);
static void	draw_export_icon(t_image *image, unsigned int background_color,
				float scale, t_vector2f offsets);
static void	draw_arrow(t_image *image, float scale, t_vector2f offsets);
static void	draw_box(t_image *image, float scale, t_vector2f offsets);

void	init_export_box(t_engine *engine, t_gui_box *gui_box)
{
	const float			min_size = fminf(gui_box->size.x, gui_box->size.y);
	const float			scale = min_size / SIZE_OF_BASE_IMAGE
		* RATIO_OF_ICON_TO_BOX;
	const bool			smaller_width = gui_box->size.x < gui_box->size.y;
	const t_vector2f	offsets = {
		.x = gui_box->size.x / 2.f - min_size / 2.f \
			+ (smaller_width * gui_box->size.x * (1.f - RATIO_OF_ICON_TO_BOX) \
				/ 2.f),
		.y = gui_box->size.y / 2.f - min_size / 2.f \
			+ (!smaller_width * gui_box->size.y * (1.f - RATIO_OF_ICON_TO_BOX) \
				/ 2.f)
	};

	gui_box->on_click = &export_box_on_click;
	init_image(&gui_box->image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	init_image(&gui_box->on_hover_image, &engine->window, gui_box->size.x,
		gui_box->size.y);
	draw_export_icon(&gui_box->image, COLOR_TRANSPARENT, scale, offsets);
	draw_export_icon(&gui_box->on_hover_image, HOVER_GUI_COLOR, scale, offsets);
}

static void	export_box_on_click(t_gui_box *self, t_engine *engine,
				t_click_data click_data)
{
	(void)self;
	if (click_data.button != BUTTON_LEFT)
		return ;
	engine->gui.message.animation_start_time_ms = ft_get_current_time_in_ms();
	engine->gui.message.time_to_appear_ms = 500;
	engine->gui.message.time_to_display_ms = 1000;
	engine->gui.message.time_to_disappear_ms = 500;
	change_image_color(&engine->gui.message.image_with_message,
		COLOR_TRANSPARENT);
	if (export_scene_with_datetime(engine) < 0)
		write_centered_string_to_image(&engine->gui.font,
			&engine->gui.message.image_with_message,
			"Scene failed to be exported");
	else
		write_centered_string_to_image(&engine->gui.font,
			&engine->gui.message.image_with_message,
			"Scene was exported");
}

static void	draw_export_icon(t_image *image,
				const unsigned int background_color, const float scale,
				const t_vector2f offsets)
{
	change_image_color(image, background_color);
	draw_arrow(image, scale, offsets);
	draw_box(image, scale, offsets);
	round_image_corners(image, BOX_ROUNDING_RADIUS);
}

static void	draw_arrow(t_image *image, const float scale,
				const t_vector2f offsets)
{
	const t_vector2f			points[] = {
		(t_vector2f){251.f, 1.f},
		(t_vector2f){260.f, 1.f},
		(t_vector2f){344.f, 85.f},
		(t_vector2f){329.f, 99.f},
		(t_vector2f){267.f, 42.f},
		(t_vector2f){267.f, 321.f},
		(t_vector2f){244.f, 321.f},
		(t_vector2f){244.f, 42.f},
		(t_vector2f){182.f, 99.f},
		(t_vector2f){167.f, 85.f}};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[9].x, points[0].y, \
													points[2].x, points[5].y};
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){scale, image,
		MENU_BOX_ICONS_COLOR, offsets.x, offsets.y});
}

static void	draw_box(t_image *image, const float scale,
				const t_vector2f offsets)
{
	const t_vector2f			points[] = {
		(t_vector2f){191.f, 154.f},
		(t_vector2f){64.f, 154.f},
		(t_vector2f){64.f, 511.f},
		(t_vector2f){447.f, 511.f},
		(t_vector2f){447.f, 154.f},
		(t_vector2f){320.f, 154.f},
		(t_vector2f){320.f, 178.f},
		(t_vector2f){423.f, 178.f},
		(t_vector2f){423.f, 487.f},
		(t_vector2f){89.f, 487.f},
		(t_vector2f){89.f, 178.f},
		(t_vector2f){191.f, 178.f}};
	t_glyph_generated_points	draw_glyph_arg;
	size_t						contours_limits;

	draw_glyph_arg.points = (t_vector2f *)points;
	draw_glyph_arg.nb_of_points = sizeof(points) / sizeof(*points);
	contours_limits = draw_glyph_arg.nb_of_points;
	draw_glyph_arg.contours_limits = &contours_limits;
	draw_glyph_arg.nb_of_contours = 1;
	draw_glyph_arg.bounds = (t_glyph_outline_bounds){points[1].x, points[0].y, \
													points[3].x, points[2].y};
	draw_glyph(&draw_glyph_arg, (t_draw_glyph_data){scale, image,
		MENU_BOX_ICONS_COLOR, offsets.x, offsets.y});
}
