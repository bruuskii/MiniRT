/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:15:39 by izouine           #+#    #+#             */
/*   Updated: 2025/02/06 08:11:25 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_vctr	calculate_ambient_lighting(t_scene *scene, t_material *material,
		t_vctr color, int in_shadow)
{
	t_vctr	ambient;

	if (in_shadow)
	{
		ambient = vec3_scale((t_vctr){50, 50, 50}, material->ambient);
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
	t_vctr		light_dir;
	t_vctr		pattern_color;
	t_sp		*sphere;

	light_dir = vec3_normalize(vec3_sub(*view->light->dir, hit.point));
	raysh = malloc(sizeof(t_ray));
	raysh->direction = &light_dir;
	t_vctr tmp = vec3_add(hit.point, hit.normal);
	raysh->origin = &tmp;
	h.color = light_colors(view->light, hit, material, view->ray);
	in_shadow = is_in_shaddow(scene, *raysh);
	sphere = (t_sp *)(scene->world->ptr);
	if (sphere && sphere->chess == 1)
	{
		pattern_color = calculate_chess_pattern(hit);
		h.color = calculate_ambient_lighting(scene, material, h.color,
				in_shadow);
		h.color = vec3_multiply(h.color, pattern_color);
	}
	else if (in_shadow)
		h.color = calculate_ambient_lighting(scene, material, h.color,
				in_shadow);
	else
		fill_dhiya(h);
	return (h.color);
}
