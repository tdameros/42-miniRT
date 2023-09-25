/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:56:18 by vfries            #+#    #+#             */
/*   Updated: 2022/12/02 18:05:21 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHAR_H
# define FT_CHAR_H

# include <stdbool.h>

//	is_in_set.c
bool	ft_is_in_set(char c, char *set);

//	isalnum.c
int		ft_isalnum(int c);

//	isalpha.c
int		ft_isalpha(int c);

//	isascii.c
int		ft_isascii(int c);

//	isdigit.c
int		ft_isdigit(int c);

//	isprint.c
int		ft_isprint(int c);

//	isspace.c
int		ft_isspace(int c);

//	tolower.c
int		ft_tolower(int c);

//	toupper.c
int		ft_toupper(int c);

#endif
