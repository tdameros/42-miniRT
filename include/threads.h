/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 03:35:21 by tdameros          #+#    #+#             */
/*   Updated: 2023/09/25 03:35:22 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

// get_routine_data.c
void	*get_routine_data(void *routine_arg_void);

// mutex.c
void	mutex_lock(void *routine_arg_void);
void	mutex_unlock(void *routine_arg_void);

//	threads.c
void	start_threads(void *arg, void *(*routine)(void *));

#endif
