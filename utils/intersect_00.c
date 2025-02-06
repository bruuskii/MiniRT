/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:12:04 by izouine           #+#    #+#             */
/*   Updated: 2025/02/06 07:28:11 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	is_zero_vector(t_vctr v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0);
}

void	ft_initialize_cone_data(t_ray *ray, t_cone *cone, t_cone_data *data)
{
	data->co = vec3_sub(*ray->origin, *(cone->vertex));
	data->v = vec3_normalize(*(cone->axis));
	data->k = ft_calculate_k(cone->tang);
}

void	ft_calculate_quadratic_coeffs(t_vctr d, t_cone_data *data)
{
	double	k_squared;

	k_squared = 1.0 + data->k * data->k;
	data->a = vec3_dot(d, d) - k_squared * vec3_dot(d, data->v) * vec3_dot(d,
			data->v);
	data->b = 2.0 * (vec3_dot(data->co, d) - k_squared * vec3_dot(d, data->v)
			* vec3_dot(data->co, data->v));
}
