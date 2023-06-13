/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:48:56 by vfries            #+#    #+#             */
/*   Updated: 2022/11/28 15:03:25 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_numbers.h"
#include <stdlib.h>
#include <stdarg.h>

char	*format_u(unsigned int n);
char	*format_x(unsigned int n, char *base);

#define HEXA_LOWER "0123456789abcdef"
#define HEXA_UPPER "0123456789ABCDEF"

char	*format_c(char c)
{
	char	*str;

	if (c == '\0')
		return ((void *)-1);
	str = malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	*str = c;
	str[1] = '\0';
	return (str);
}

char	*format_s(char *str)
{
	if (str == NULL)
		return (ft_strdup("(null)"));
	return (ft_strdup(str));
}

char	*format_p(size_t n, char *base)
{
	char	buf[19];
	char	*buf_ptr;

	if (n == 0)
		return (ft_strdup("0x0"));
	buf[18] = '\0';
	buf_ptr = buf + 17;
	while (n != 0)
	{
		*buf_ptr-- = base[n % 16];
		n /= 16;
	}
	*buf_ptr-- = 'x';
	*buf_ptr = '0';
	return (ft_strdup(buf_ptr));
}

char	*format(const char **str_format, va_list *args)
{
	if (**str_format == 'c')
		return (format_c(va_arg(*args, int)));
	if (**str_format == 's')
		return (format_s(va_arg(*args, char *)));
	if (**str_format == 'p')
		return (format_p(va_arg(*args, size_t), HEXA_LOWER));
	if (**str_format == 'd' || **str_format == 'i')
		return (ft_itoa(va_arg(*args, int)));
	if (**str_format == 'u')
		return (format_u(va_arg(*args, unsigned int)));
	if (**str_format == 'x')
		return (format_x(va_arg(*args, unsigned int), HEXA_LOWER));
	if (**str_format == 'X')
		return (format_x(va_arg(*args, unsigned int), HEXA_UPPER));
	if (**str_format == '%')
		return (ft_strdup("%"));
	(*str_format)--;
	return ((void *)-2);
}
