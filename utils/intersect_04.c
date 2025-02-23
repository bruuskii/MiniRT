/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:12:01 by izouine           #+#    #+#             */
/*   Updated: 2025/02/23 10:48:31 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	ft_calculate_discriminant(t_cone_data *data)
{
	double	c;

	c = vec3_dot(data->co, data->co) - (1.0 + data->k * data->k)
		* vec3_dot(data->co, data->v) * vec3_dot(data->co, data->v);
	data->discriminant = data->b * data->b - 4.0 * data->a * c;
	return (data->discriminant);
}

int	ft_valid_cone_inter(t_cone *cn, t_ray *ray, double t1, double t2)
{
	t_vctr	hitpoint_1;
	t_vctr	tmp;
	t_vctr	hitpoint_2;
	double	height_1;
	double	height_2;

	cn->height = cn->maxm - cn->minm;
	tmp = vec3_create(cn->vertex->x - cn->height, cn->vertex->y - cn->height,
			cn->vertex->z - cn->height);
	hitpoint_1 = vec3_add(*ray->origin, vec3_scale(*ray->direction, t1));
	hitpoint_2 = vec3_add(*ray->origin, vec3_scale(*ray->direction, t2));
	height_1 = vec3_dot(vec3_sub(hitpoint_1, tmp), *cn->axis);
	height_2 = vec3_dot(vec3_sub(hitpoint_2, tmp), *cn->axis);
	if ((t1 > 1e-6 && height_1 >= 0 && height_1 <= cn->height) && (t2 > 1e-6
			&& height_2 >= 0 && height_2 <= cn->height))
		return (2);
	else if (t1 > 1e-6 && height_1 >= 0 && height_1 <= cn->height)
		return (3);
	else if (t2 > 1e-6 && height_2 >= 0 && height_2 <= cn->height)
		return (4);
	else
		return (1);
	return (0);
}

int	ft_solve_quadratic(t_cone_data *data, double *t, t_cone *cn, t_ray *ray)
{
	double	t0;
	double	t1;
	int		res;

	t0 = (-data->b - sqrt(data->discriminant)) / (2.0 * data->a);
	t1 = (-data->b + sqrt(data->discriminant)) / (2.0 * data->a);
	res = ft_valid_cone_inter(cn, ray, t0, t1);
	if (res == 2)
	{
		if (t0 < t1)
			*t = t0;
		else
			*t = t1;
	}
	else if (res == 3)
		*t = t0;
	else if (res == 4)
		*t = t1;
	return (res);
}

int	ft_validate_and_solve(t_cone_data *data, double *t, t_cone *cn, t_ray *ray)
{
	if (data->discriminant < 0)
		return (1);
	return (ft_solve_quadratic(data, t, cn, ray));
}

int	ft_check_intersection_constraints(t_vctr intersection, t_cone *cone,
		t_vctr v, t_hit *hit)
{
	t_vctr	hit_to_vertex;
	double	m;
	t_vctr	normal;

	hit_to_vertex = vec3_sub(intersection, *(cone->vertex));
	m = vec3_dot(hit_to_vertex, v);
	if (m < cone->minm || m > cone->maxm)
		return (1);
	normal = vec3_sub(hit_to_vertex, vec3_scale(v, m));
	hit->normal = vec3_normalize(normal);
	return (0);
}
