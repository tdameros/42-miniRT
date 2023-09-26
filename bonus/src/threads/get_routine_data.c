/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_routine_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:52:38 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/23 22:52:39 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "threads_private_header.h"

void	*get_routine_data(void *routine_arg_void)
{
	return (((t_routine_arg *)routine_arg_void)->data);
}
