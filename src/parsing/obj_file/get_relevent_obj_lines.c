#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "libft.h"
#include "mesh.h"

int	fill_lines(t_str_vector *lines, const int fd,
		t_size_to_allocate_in_mesh size_of_mesh_content);

t_str_vector	get_relevent_obj_lines(const char *file_name,
					size_t *number_of_vertex, size_t *number_of_normals,
					size_t *number_of_faces)
{
	const int		fd = open(file_name, O_RDONLY);
	t_str_vector	lines;

	*number_of_vertex = 0;
	*number_of_normals = 0;
	*number_of_faces = 0;
	if (fd < 0)
		return ((t_vector){NULL, 0, 0, 0});
	if (ft_str_vector_create(&lines, 10000) != VECTOR_SUCCESS)
	{
		close(fd);
		return ((t_vector){NULL, 0, 0, 0});
	}
	if (fill_lines(&lines, fd, (t_size_to_allocate_in_mesh){
			number_of_vertex, number_of_normals, number_of_faces}) < 0)
	{
		close(fd);
		ft_str_vector_destroy(&lines);
		return ((t_vector){NULL, 0, 0, 0});
	}
	return (lines);
}

int	fill_lines(t_str_vector *lines, const int fd,
		t_size_to_allocate_in_mesh size_of_mesh_content)
{
	char	*line;

	errno = 0;
	line = get_next_line(fd);
	while (line != NULL || errno != 0)
	{
		if (errno != 0)
			return (free(line), -1);
		if (ft_strncmp(line, "v ", 2) == 0)
			(*size_of_mesh_content.number_of_vertex)++;
		else if (ft_strncmp(line, "vn ", 3) == 0)
			(*size_of_mesh_content.number_of_normals)++;
		else if (ft_strncmp(line, "f ", 2) == 0)
			(*size_of_mesh_content.number_of_faces)++;
		else
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (ft_str_vector_add_elem(lines, line) != VECTOR_SUCCESS)
			return (free(line), -1);
		line = get_next_line(fd);
	}
	return (0);
}
