/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:40:01 by vfries            #+#    #+#             */
/*   Updated: 2023/07/30 18:40:13 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "math/vector.h"

static t_put_image_to_image_data	init_put_image_to_image(t_image *dst,
										const t_image *src,
										t_vector2i position);

void	put_image_to_image(t_image *dst, const t_image *src,
			t_vector2i position)
{
	register t_put_image_to_image_data	data;
	register unsigned int				*dst_cursor;
	register const unsigned int			*src_cursor;

	data = init_put_image_to_image(dst, src, position);
	while (data.next_dst_line < dst->limit
		&& data.next_src_line < src->limit)
	{
		dst_cursor = data.next_dst_line + data.dst_x_start;
		src_cursor = data.next_src_line + data.src_x_start;
		data.next_dst_line += dst->width;
		data.next_src_line += src->width;
		while (dst_cursor < data.next_dst_line
			&& src_cursor < data.next_src_line)
		{
			*dst_cursor = mix_colors(*src_cursor, *dst_cursor);
			dst_cursor++;
			src_cursor++;
		}
	}
}

static t_put_image_to_image_data	init_put_image_to_image(t_image *dst,
										const t_image *src, t_vector2i position)
{
	t_put_image_to_image_data	data;

	if (position.y > 0)
	{
		data.next_dst_line = dst->address + position.y * dst->width;
		data.next_src_line = src->address;
	}
	else
	{
		data.next_dst_line = dst->address;
		data.next_src_line = src->address + (-position.y) * src->width;
	}
	if (position.x > 0)
	{
		data.src_x_start = 0;
		data.dst_x_start = position.x;
	}
	else
	{
		data.src_x_start = -position.x;
		data.dst_x_start = 0;
	}
	return (data);
}
