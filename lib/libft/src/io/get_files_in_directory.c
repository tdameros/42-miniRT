#include <dirent.h>
#include <stdlib.h>

#include "ft_vector.h"
#include "ft_string.h"

static int	get_all_files_in_directory(t_vector *files, const char *path);
static char	**get_files_with_correct_extension(t_vector *files_vector,
				const char *extension);

///
/// \param path path to the directory which files you want to get
/// \param extension extension of the files you want to get (NULL if you want to
/// get all files)
/// \return
char	**ft_get_files_in_directory(const char *path, const char *extension)
{
	t_vector	files;

	if (path == NULL)
		return (NULL);
	if (get_all_files_in_directory(&files, path) < 0)
		return (NULL);
	if (extension == NULL)
		return (ft_str_vector_to_strs(&files, false, true));
	return (get_files_with_correct_extension(&files, extension));
}

static int	get_all_files_in_directory(t_vector *files, const char *path)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*file;

	directory = opendir(path);
	if (directory == NULL)
		return (-1);
	ft_vector_create(files, sizeof(char *), 0);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			file = ft_strjoin_three(path, "/", entry->d_name);
			if (file == NULL
				|| ft_vector_add_elem(files, &file) != VECTOR_SUCCESS)
				return (ft_str_vector_destroy(files), free(file),
					closedir(directory), -1);
		}
		entry = readdir(directory);
	}
	closedir(directory);
	return (0);
}

static char	**get_files_with_correct_extension(t_vector *files_vector,
				const char *extension)
{
	t_vector	files_with_correct_extension;
	size_t		i;

	ft_vector_create(&files_with_correct_extension, sizeof(char *), 0);
	i = -1;
	while (++i < files_vector->length)
	{
		if (ft_str_ends_with(ft_str_vector_get_elem(files_vector, i),
				extension))
		{
			if (ft_vector_add_elem(&files_with_correct_extension,
					ft_vector_get_ptr_to_elem(files_vector, i))
				!= VECTOR_SUCCESS)
				return (ft_str_vector_destroy(files_vector), \
						ft_str_vector_destroy(&files_with_correct_extension), \
						NULL);
			*(char **)ft_vector_get_ptr_to_elem(files_vector, i) = NULL;
		}
	}
	ft_str_vector_destroy(files_vector);
	return (ft_str_vector_to_strs(&files_with_correct_extension, false, true));
}
