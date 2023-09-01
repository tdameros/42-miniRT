/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:13:47 by tdameros          #+#    #+#             */
/*   Updated: 2023/07/31 09:13:55 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include <sys/time.h>
# include <stdint.h>

# define NB_OF_USECONDS_IN_A_SECOND 1000000
# define NB_OF_USECONDS_IN_A_MILLISECOND 1000

uint64_t		ft_timeval_to_ms(struct timeval time);
struct timeval	ft_get_current_time(void);
uint64_t		ft_get_current_time_in_ms(void);
int				ft_get_number_of_fps(struct timeval start_time);
float			ft_get_time_elapsed_in_seconds(struct timeval start_time);

#endif
