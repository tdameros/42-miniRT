/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:07:00 by vfries            #+#    #+#             */
/*   Updated: 2023/05/27 20:07:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_H
# define OPENCL_H

# include <CL/cl.h>

typedef struct s_opencl
{
	cl_device_id		deviceID;
	cl_context			context;
	cl_command_queue	commandQueue;
}	t_opencl;

#endif
