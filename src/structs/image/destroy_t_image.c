#include "libft.h"
#include "mlx.h"

#include "struct/t_minirt.h"
#include "struct/t_image.h"

void	destroy_t_image(t_window *minirt_window, t_image *image)
{
	if (image->data != NULL)
		mlx_destroy_image(minirt_window->mlx, image->data);
	ft_bzero(image, sizeof(*image));
}
