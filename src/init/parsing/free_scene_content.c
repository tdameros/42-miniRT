#include <stdlib.h>

#include "libft.h"

void	free_scene_content(char ***scene_content)
{
	size_t	i;

	i = 0;
	while (scene_content[i] != NULL)
	{
		ft_free_split(scene_content[i]);
		i++;
	}
	free(scene_content);
}
