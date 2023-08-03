#include <math.h>

#include "image.h"
#include "colors.h"
#include "gui/utils.h"

#define BASE_IMAGE_SIZE 1024.f
#define TRANSPARENT_CERCLE_RADIUS 200
#define COLOR_CERCLE_RADIUS 275

void	draw_light_icon(t_image *image,
			const unsigned int background_color, const t_color vec_color)
{
	const float			image_min_size = fminf(image->width, image->height);
	const float			scale = image_min_size / BASE_IMAGE_SIZE;
	const t_vector2f	center = {image->width / 2.f, image->height / 2.f};
	const unsigned int	color = vec_rgb_to_uint(vec_color);
	const t_vector2f	offset = {.x = image->width / 2.f - image_min_size / 2.f, \
								.y = image->height / 2.f - image_min_size / 2.f};

	change_image_color(image, background_color);
	draw_top_rectangles(image, color, scale, offset);
	draw_bottom_rectangles(image, color, scale, offset);
	draw_side_rectangles(image, color, scale, offset);
	image_draw_circle(image, center, COLOR_CERCLE_RADIUS * scale, color);
	image_draw_circle(image, center, TRANSPARENT_CERCLE_RADIUS * scale,
		background_color);
}
