/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_segments_intersect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:03:00 by vfries            #+#    #+#             */
/*   Updated: 2023/06/24 16:03:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

#include "math/vector.h"

static int	orientation(t_vector2d p, t_vector2d q, t_vector2d r);
static bool	on_segment(t_vector2d p, t_vector2d q, t_vector2d r);

#define A 0
#define B 1
#define C 2
#define D 3

bool	do_segments_intersect(t_vector2f a, t_vector2f b, t_vector2f c,
			t_vector2f d)
{
	const t_vector2d	points[4] = {{a.x, a.y}, {b.x, b.y},
			{c.x, c.y}, {d.x, d.y}};
	const int 			o1 = orientation(points[A], points[B], points[C]);
	const int 			o2 = orientation(points[A], points[B], points[D]);
	const int 			o3 = orientation(points[C], points[D], points[A]);
	const int 			o4 = orientation(points[C], points[D], points[B]);

	if (o1 != o2 && o3 != o4)
		return (true);
	if (o1 == 0 && on_segment(points[A], points[C], points[B]))
		return (true);
	if (o2 == 0 && on_segment(points[A], points[D], points[B]))
		return (true);
	if (o3 == 0 && on_segment(points[C], points[A], points[D]))
		return (true);
	if (o4 == 0 && on_segment(points[C], points[B], points[D]))
		return (true);
	return (false);
}

static int	orientation(t_vector2d p, t_vector2d q, t_vector2d r)
{
	const double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (fabs(val) < 1e-9)
		return (0);
	if (val > 0)
		return (1);
	else
		return (2);
}

static bool	on_segment(t_vector2d p, t_vector2d q, t_vector2d r)
{
	return (q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) &&
		q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y));
}
