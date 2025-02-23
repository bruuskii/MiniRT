/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:20 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/23 11:43:54 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vctr	ft_final_color(t_ray *ray, t_hit *hit, t_scene *scene, t_material *mtrl)
{
	t_vctr	final_color;
	t_light	*light;
	t_vctr	light_color;
	t_view	*view;

	final_color = (t_vctr){0, 0, 0};
	light = scene->light;
	while (light)
	{
		view = ft_view(final_color, final_color, light, ray);
		if (!view)
			continue ;
		light_color = calculate_lighting(view, *hit, scene, mtrl);
		final_color.x += light_color.x;
		final_color.y += light_color.y;
		final_color.z += light_color.z;
		free(view);
		if (light)
			light = light->next;
	}
	final_color.x = fmin(fmax(final_color.x, 0), 255);
	final_color.y = fmin(fmax(final_color.y, 0), 255);
	final_color.z = fmin(fmax(final_color.z, 0), 255);
	return (final_color);
}

void	ft_innit_hit_sp(t_ray *ray, t_world *tp, t_hit **hit)
{
	t_sp	*sp;

	sp = (t_sp *)tp->ptr;
	*hit = intersect_sphere(ray, sp);
	if (*hit)
	{
		(*hit)->type = SPHERE;
		(*hit)->world = tp;
		if ((*hit)->world->fl)
			(*hit)->fl = 1;
	}
}

void	ft_innit_hit_pl(t_ray *ray, t_world *tp, t_hit **hit)
{
	t_plane	*plane;

	plane = (t_plane *)tp->ptr;
	*hit = intersect_plane(ray, plane);
	if (*hit)
	{
		(*hit)->type = PLANE;
		(*hit)->world = tp;
		if ((*hit)->world->fl)
			(*hit)->fl = 1;
	}
}

void	ft_innit_hit_cy(t_ray *ray, t_world *tp, t_hit **hit)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)tp->ptr;
	*hit = intersect_cylinder(ray, cy);
	if (*hit)
	{
		(*hit)->type = CYLINDRE;
		(*hit)->world = tp;
		if ((*hit)->world->fl)
			(*hit)->fl = 1;
	}
}

void	ft_innit_hit_cn(t_ray *ray, t_world *tp, t_hit **hit)
{
	t_cone	*cn;

	cn = (t_cone *)tp->ptr;
	*hit = intersect_cone(ray, cn);
	if (*hit)
	{
		(*hit)->type = CONE;
		(*hit)->world = tp;
		if ((*hit)->world->fl)
			(*hit)->fl = 1;
	}
}
