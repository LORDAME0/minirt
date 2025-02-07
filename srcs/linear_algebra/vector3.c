/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:06:08 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/09 21:39:30 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

bool	is_equal_float(float x, float y)
{
	return (fabsf(x - y) < EPSILON);
}

bool	is_equal_double(double x, double y)
{
	return (fabs(x - y) < EPSILON);
}

bool	vec_is_equal(t_vec v1, t_vec v2)
{
	return (is_equal_double(v1.x, v2.x)
		&& is_equal_double(v1.y, v2.y)
		&& is_equal_double(v1.z, v2.z));
}

inline t_vec	vector(double x, double y, double z)
{
	return ((t_vec){{x, y, z, 0}});
}

inline t_point	point(double x, double y, double z)
{
	return ((t_point){{x, y, z, 1}});
}
