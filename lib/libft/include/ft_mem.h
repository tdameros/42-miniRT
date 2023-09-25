/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:04:20 by vfries            #+#    #+#             */
/*   Updated: 2022/11/19 11:06:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEM_H
# define FT_MEM_H

# include <stddef.h>

//	bzero.c
void	ft_bzero(void *s, size_t n);

//	calloc.c
void	*ft_calloc(size_t count, size_t size);

//	memchr.c
void	*ft_memchr(const void *s, int c, size_t n);

//	memcmp.c
int		ft_memcmp(const void *s1, const void *s2, size_t n);

//	memcpy.c
void	*ft_memcpy(void *dst, const void *src, size_t n);

//	memmove.c
void	*ft_memmove(void *dst, const void *src, size_t len);

//	memset.c
void	*ft_memset(void *b, int c, size_t len);

#endif