/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:15:39 by izouine           #+#    #+#             */
/*   Updated: 2025/01/25 00:08:23 by kbassim          ###   ########.fr       */
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

static t_vctr	calculate_chess_pattern(t_hit hit)
{
	t_helpers	helper;

	helper.u = 0.5 + atan2(hit.normal.z, hit.normal.x) / (2 * M_PI);
	helper.v = 0.5 - asin(hit.normal.y) / M_PI;
	helper.square_u = floor(helper.u * 16);
	helper.square_v = floor(helper.v * 16);
	helper.white.x = 255.0;
	helper.white.y = 255.0;
	helper.white.z = 255.0;
	helper.black.x = 0.0;
	helper.black.y = 0.0;
	helper.black.z = 0.0;
	if ((helper.square_u + helper.square_v) % 2 == 0)
		return (helper.white);
	else
		return (helper.black);
}

void	fill_dhiya(t_helpers h)
{
	h.color.x = fmin(fmax(h.color.x, 0.0), 255.0);
	h.color.y = fmin(fmax(h.color.y, 0.0), 255.0);
	h.color.z = fmin(fmax(h.color.z, 0.0), 255.0);
}

t_vctr	calculate_lighting(t_view *view, t_hit hit, t_scene *scene,
		t_material *material)
{
	t_helpers	h;
	int			in_shadow;
	t_vctr		light_dir;
	t_vctr		pattern_color;

	light_dir = vec3_normalize(vec3_sub(*view->light->dir, hit.point));
	h.raysh.direction = light_dir;
	h.raysh.origin = vec3_add(hit.point, hit.normal);
	h.color = light_colors(view->light, hit, material, view->ray);
	in_shadow = is_in_shaddow(scene, h.raysh);
	if (scene->sp && scene->sp->chess == 1)
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
