/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:20 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/17 04:01:56 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vctr	amb_color(t_vctr ambiant, t_material *mtrl)
{
	t_vctr	amb;
	t_vctr	color;
	double	ambient;

	color = mtrl->color;
	ambient = mtrl->ambient;
	amb.x = ambiant.x * color.x * ambient / 255;
	amb.y = ambiant.y * color.y * ambient / 255;
	amb.z = ambiant.z * color.z * ambient / 255;
	return (amb);
}

t_ray	*get_ray(t_scene *scene, double x, double y)
{
	t_ray	*ray;

	ray = create_ray(scene->cam, x, y);
	if (!ray)
		return (NULL);
	return (ray);
}

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

t_hit	*ft_innit_hit(t_ray *ray, t_world *tp)
{
	t_hit	*hit;

	hit = NULL;
	if (tp->type == 0)
		ft_innit_hit_sp(ray, tp, &hit);
	else if (tp->type == 1)
		ft_innit_hit_pl(ray, tp, &hit);
	else if (tp->type == 2)
		ft_innit_hit_cy(ray, tp, &hit);
	else if (tp->type == 5)
		ft_innit_hit_cn(ray, tp, &hit);
	return (hit);
}

void	ft_get_hit_color(t_world *world, t_hit *hit)
{
	t_sp		*sp;
	t_cone		*cone;
	t_plane		*plane;
	t_cylinder	*cy;

	if (hit->type == SPHERE)
	{
		sp = (t_sp *)world->ptr;
		hit->mtrl->color = *sp->color;
	}
	else if (hit->type == PLANE)
	{
		plane = (t_plane *)world->ptr;
		hit->mtrl->color = *plane->color;
	}
	else if (hit->type == CYLINDRE)
	{
		cy = (t_cylinder *)world->ptr;
		hit->mtrl->color = *cy->color;
	}
	else if (hit->type == CONE)
	{
		cone = (t_cone *)world->ptr;
		hit->mtrl->color = *cone->color;
	}
}

void	ft_free_hit_elems(t_hit *hit)
{
	free(hit->mtrl);
	free(hit);
}

t_hit	*ft_get_hit(t_ray *ray, t_world *world)
{
	t_hit	*hit;
	t_hit	*c_hit;
	t_world	*tp;

	hit = NULL;
	c_hit = NULL;
	tp = world;
	while (tp)
	{
		hit = ft_innit_hit(ray, tp);
		if (hit && hit->hit)
		{
			ft_get_hit_color(tp, hit);
			if (!c_hit || hit->t < c_hit->t)
			{
				if (c_hit)
					ft_free_hit_elems(c_hit);
				c_hit = hit;
			}
			else
				ft_free_hit_elems(hit);
		}
		tp = tp->next;
	}
	return (c_hit);
}
