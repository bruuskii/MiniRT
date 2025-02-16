/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:11:58 by izouine           #+#    #+#             */
/*   Updated: 2025/02/07 22:15:30 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	ft_discriminant_cylinder(t_ray *ray, t_cylinder *cy, t_vctr oc)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = vec3_dot(*ray->direction, *ray->direction)
		- pow(vec3_dot(*ray->direction, *cy->c_axis), 2);
	b = 2 * (vec3_dot(*ray->direction, oc) - vec3_dot(*ray->direction,
				*cy->c_axis) * vec3_dot(oc, *cy->c_axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, *cy->c_axis), 2) - pow(cy->d / 2,
			2);
	discriminant = b * b - 4 * a * c;
	return (discriminant);
}

double	ft_magnitude(t_vctr vct)
{
	return (sqrt(vct.x * vct.x + vct.y * vct.y + vct.z * vct.z));
}

double	ft_calculate_k(double tang)
{
	return (tan(tang * M_PI / 180.0));
}
