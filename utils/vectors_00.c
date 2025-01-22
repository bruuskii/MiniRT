/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:21:13 by izouine           #+#    #+#             */
/*   Updated: 2025/01/22 22:21:14 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vctr	vec3_add(t_vctr v1, t_vctr v2)
{
	return (vec3_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vctr	vec3_sub(t_vctr v1, t_vctr v2)
{
	return (vec3_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vctr	vec3_scale(t_vctr v, double t)
{
	return (vec3_create(v.x * t, v.y * t, v.z * t));
}

void	ft_print_and_exit(char *s, int stat)
{
	printf("%s%s\n", ERROR_MESSAGE, s);
	exit(stat);
}

t_vctr	vec3_cross(t_vctr v1, t_vctr v2)
{
	return (vec3_create(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}
