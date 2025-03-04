/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_06.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:46:01 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/04 19:39:37 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
	ft_calculate_quadratic_coeffs(*ray->direction, &data);
	ft_calculate_discriminant(&data);
	if (ft_validate_and_solve(&data, &t, cone, ray) == 1)
		return (free(hit->mtrl), free(hit), NULL);
	intersection = vec3_add(*ray->origin, vec3_scale(vec3_normalize(*ray->direction), t));
	if (ft_check_intersection_constraints(intersection, cone, data.v, hit))
		return (free(hit->mtrl), free(hit), NULL);
	hit->t = t;
	hit->hit = 1;
	hit->point = intersection;
	return (hit);
}
