#include <stdlib.h>
#include "mlx.h"

#include "struct/t_minirt.h"

int	close_minirt(t_minirt *minirt)
{
	mlx_destroy_window(minirt->window.mlx, minirt->window.window);
	exit(0); // TODO: free everything
}
