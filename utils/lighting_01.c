/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:15:39 by izouine           #+#    #+#             */
/*   Updated: 2025/02/06 22:30:45 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_vctr	calculate_ambient_lighting(t_scene *scene, t_material *material,
		t_vctr color, int in_shadow)
{
	t_vctr	ambient;

	if (in_shadow)
	{
		ambient = vec3_scale((t_vctr){10, 10, 10}, material->ambient);
		color = vec3_scale(vec3_add(ambient, color), 0.5);
	}
	else
	{
		ambient = vec3_scale(*scene->alight->color, material->ambient);
		color = vec3_add(color, ambient);
	}
	return (color);
}

t_vctr	calculate_lighting(t_view *view, t_hit hit, t_scene *scene,
		t_material *material)
{
	t_helpers	h;
	int			in_shadow;
	t_ray       *raysh;

	raysh = malloc(sizeof(t_ray));
	raysh->direction = view->light->dir;
	if (hit.type == PLANE)
		material->type = 1;
	t_vctr tmp = hit.point;
	raysh->origin = &tmp;
	h.color = light_colors(view->light, hit, material, view->ray);
	in_shadow = is_in_shaddow(scene, *raysh);
	if (raysh)
		free(raysh);
	if (in_shadow)
		h.color = calculate_ambient_lighting(scene, material, h.color,
				in_shadow);
	else
	 	fill_dhiya(h);
	return (h.color);
}
