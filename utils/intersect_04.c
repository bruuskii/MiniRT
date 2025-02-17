/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:12:01 by izouine           #+#    #+#             */
/*   Updated: 2025/02/06 07:28:11 by kbassim          ###   ########.fr       */
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

int	ft_solve_quadratic(double a, double b, double discriminant, double *t)
{
	double	t0;
	double	t1;

	t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t0 > 1e-6 && t1 > 1e-6)
	{
		*t = fmin(t0, t1);
		return (0);
	}
	else if (t0 > 1e-6)
	{
		*t = t0;
		return (0);
	}
	else if (t1 > 1e-6)
	{
		*t = t1;
		return (0);
	}
	return (1);
}

int	ft_validate_and_solve(t_cone_data *data, double *t)
{
	if (data->discriminant < 0)
		return (1);
	return (ft_solve_quadratic(data->a, data->b, data->discriminant, t));
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

t_hit	*intersect_cone(t_ray *ray, t_cone *cone)
{
	t_hit		*hit;
	t_cone_data	data;
	double		t;
	t_vctr		intersection;

	if (!ray || !cone)
		return (NULL);
	hit = ft_hit();
	if (!hit)
		return (NULL);
	ft_initialize_cone_data(ray, cone, &data);
	ft_calculate_quadratic_coeffs(vec3_normalize(*ray->direction), &data);
	ft_calculate_discriminant(&data);
	if (ft_validate_and_solve(&data, &t))
		return (free(hit->mtrl), free(hit), NULL);
	intersection = vec3_add(*ray->origin,
			vec3_scale(vec3_normalize(*ray->direction), t));
	if (ft_check_intersection_constraints(intersection, cone, data.v, hit))
		return (free(hit->mtrl), free(hit), NULL);
	hit->t = t;
	hit->hit = 1;
	hit->point = intersection;
	return (hit);
}
