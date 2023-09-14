#include "threads_private_header.h"

void	*get_routine_data(void *routine_arg_void)
{
	return (((t_routine_arg *)routine_arg_void)->data);
}
