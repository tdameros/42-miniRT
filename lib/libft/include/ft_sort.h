/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:13:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/27 18:13:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_H
# define FT_SORT_H

int	ft_msort_int(int *tab, int index_left, int index_right);
int	ft_msort_str(char **tab, int index_left, int index_right);
int	ft_msort_str_ignore_case(char **tab, int index_left, int index_right);

#endif
