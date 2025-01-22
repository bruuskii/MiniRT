/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:21:18 by izouine           #+#    #+#             */
/*   Updated: 2025/01/22 22:22:22 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	vec3_dot(t_vctr v1, t_vctr v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vctr	vec3_normalize(t_vctr v)
{
	double	length;

	length = sqrt(vec3_dot(v, v));
	if (length == 0)
		return (vec3_create(0, 0, 0));
	return (vec3_scale(v, 1 / length));
}

t_vctr	vec3_create(double x, double y, double z)
{
	t_vctr	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
