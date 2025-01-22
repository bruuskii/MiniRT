/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:15:39 by izouine           #+#    #+#             */
/*   Updated: 2025/01/22 22:15:40 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vctr	calculate_lighting(t_view *view, t_hit hit, t_scene *scene,
		t_material *material)
{
	t_vctr	color;
	t_ray	raysh;
	int		in_shadow;
	t_vctr	ambient;
	t_vctr	light_dir;

	light_dir = vec3_normalize(vec3_sub(*view->light->dir, hit.point));
	raysh.direction = light_dir;
	raysh.origin = vec3_add(hit.point, hit.normal);
	color = light_colors(view->light, hit, material, view->ray);
	in_shadow = is_in_shaddow(scene, raysh);
	if (in_shadow)
	{
		ambient = vec3_scale((t_vctr){10, 10, 10}, material->ambient);
		color = vec3_scale(vec3_add(ambient, color), 0.5);
	}
	else
	{
		color.x = fmin(fmax(color.x, 0.0), 255.0);
		color.y = fmin(fmax(color.y, 0.0), 255.0);
		color.z = fmin(fmax(color.z, 0.0), 255.0);
	}
	return (color);
}
