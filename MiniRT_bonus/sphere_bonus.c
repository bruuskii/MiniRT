/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:49:08 by izouine           #+#    #+#             */
/*   Updated: 2025/01/22 22:59:23 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_checker(t_hit *hit, t_vctr original_normal)
{
	double	bump_intensity;
	double	noise_x;
	double	noise_y;
	double	noise_z;
	t_vctr	noise_offset;

	bump_intensity = 0.1;
	noise_x = fmod(sin(hit->point.x * 10), 1.0);
	noise_y = fmod(cos(hit->point.y * 10), 1.0);
	noise_z = fmod(tan(hit->point.z * 10), 1.0);
	noise_offset = (t_vctr){noise_x * bump_intensity, noise_y * bump_intensity,
		noise_z * bump_intensity};
	hit->normal = vec3_normalize(vec3_add(original_normal, noise_offset));
}

void	ft_chess_sphere(t_scene *t_scene, t_vctr color)
{
	t_helpers	helper;

	if (scene->sp && scene->sp->chess == 1)
	{
		helper.u = 0.5 + atan2(normal.z, normal.x) / (2 * M_PI);
		helper.v = 0.5 - asin(normal.y) / M_PI;
		helper.square_u = floor(helper.u * 16);
		helper.square_v = floor(helper.v * 16);
		helper.white = {255.0, 255.0, 255.0};
		helper.black = {0.0, 0.0, 0.0};
		if ((helper.square_u + helper.square_v) % 2 == 0)
			helper.pattern_color = helper.white;
		else
			helper.pattern_color = helper.black;
		if (helper.lol->hit && !helper.lol->t)
		{
			free(helper.lol);
			helper.shadowed = vec3_scale(color, -1);
			return (vec3_multiply(shadowed, pattern_color));
		}
		free(helper.lol);
		helper.ambient = vec3_scale(*scene->alight->color, material->ambient);
		color = vec3_add(color, helper.ambient);
		color = vec3_multiply(color, helper.pattern_color);
	}
}

void	ft_chess_plane(t_scene *scene, t_vctr color)
{
	t_helpers	helper;

	if (scene->plane && scene->plane->chess == 1)
	{
		helper.square_x = floor(hit_point.x * 2.0);
		helper.square_z = floor(hit_point.z * 2.0);
		helper.white = (t_vctr){255.0, 255.0, 255.0};
		helper.black = (t_vctr){0.0, 0.0, 0.0};
		if ((helper.square_x + helper.square_z) % 2 == 0)
			helper.pattern_color = helper.white;
		else
			helper.pattern_color = helper.black;
		if (helper.lol->hit && !helper.lol->t)
		{
			free(helper.lol);
			helper.shadowed = vec3_scale(color, -1);
			return (vec3_multiply(helper.shadowed, helper.pattern_color));
		}
		free(helper.lol);
		helper.ambient = vec3_scale(*scene->alight->color, material->ambient);
		color = vec3_add(color, helper.ambient);
		color = vec3_multiply(color, helper.pattern_color);
	}
}

void	ft_chess_cylinder(t_scene *scene, t_vctr color)
{
	t_helpers	helper;

	if (scene->cy && scene->cy->chess == 1)
	{
		helper.angle = atan2(normal.z, normal.x) / (2 * M_PI) + 0.5;
		helper.height = hit_point.y;
		helepr.square_angle = floor(helper.angle * 8);
		helper.square_height = floor(helper.height * 2.0);
		helper.white = (t_vctr){255.0, 255.0, 255.0};
		helper.black = (t_vctr){0.0, 0.0, 0.0};
		if ((helper.square_angle + helper.square_height) % 2 == 0)
			helper.pattern_color = helper.white;
		else
			helper.pattern_color = helper.black;
		if (helper.lol->hit && !helper.lol->t)
		{
			free(helper.lol);
			helper.shadowed = vec3_scale(color, -1);
			return (vec3_multiply(helper.shadowed, helper.pattern_color));
		}
		free(helper.lol);
		helper.ambient = vec3_scale(*scene->alight->color, material->ambient);
		color = vec3_add(color, helper.ambient);
		color = vec3_multiply(color, hepler.pattern_color);
	}
}

void	ft_chess_cone(t_scene *scene, t_vctr color)
{
	t_helpers	hl;

	if (scene->cone && scene->cone->chess == 1)
	{
		hl.angle = atan2(normal.z, normal.x) / (2 * M_PI) + 0.5;
		hl.height = hit_point.y;
		hl.radius = hl.height * tan(scene->cone->angle);
		hl.square_angle = floor(hl.angle * (8.0 + 4.0 * hl.radius));
		hl.square_height = floor(hl.height * 2.0);
		hl.white = (t_vctr){255.0, 255.0, 255.0};
		hl.black = (t_vctr){0.0, 0.0, 0.0};
		if ((hl.square_angle + hl.square_height) % 2 == 0)
			hl.pattern_color = hl.white;
		else
			hl.pattern_color = hl.black;
		if (hl.lol->hit && !hl.lol->t)
		{
			hl.shadowed = vec3_scale(color, -1);
			return (free(hl.lol), vec3_multiply(hl.shadowed, hl.pattern_color));
		}
		free(hl.ambient);
		hl.ambient = vec3_scale(*scene->alight->color, material->ambient);
		color = vec3_add(color, hl.ambient);
		color = vec3_multiply(color, hl.pattern_color);
	}
}
