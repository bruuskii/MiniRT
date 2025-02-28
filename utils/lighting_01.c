/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:15:39 by izouine           #+#    #+#             */
/*   Updated: 2025/02/28 01:00:36 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vctr	phong_lighting(t_view *view, t_vctr normal, t_material *material)
{
	double	ambient;
	double	diffuse;
	double	specular;
	t_vctr	color;
	t_vctr	reflect_dir;

	reflect_dir = vec3_normalize(vec3_sub(vec3_scale(normal, 2 * vec3_dot(normal,
					view->light_dir)), view->light_dir));
	ambient = material->ambient;
	diffuse = fmax(vec3_dot(normal, view->light_dir), 0.0) * material->diffuse;
	specular = pow(fmax(vec3_dot(view->view_dir, reflect_dir), 0.0),
			material->shininess) * material->specular;
	color = vec3_scale(material->color, ambient + diffuse);
	color = vec3_add(color, vec3_scale(*view->light->color, specular));
	color = vec3_scale(color, view->light->brightness);
	return (vec3_create(fmin(color.x, 255.0), fmin(color.y, 255.0),
			fmin(color.z, 255.0)));
}

t_view	*ft_view(t_vctr light_dir, t_vctr view_dir, t_light *light, t_ray *ray)
{
	t_view	*ptr;

	ptr = malloc(sizeof(t_view));
	if (!ptr)
		return (NULL);
	ptr->light_dir = light_dir;
	ptr->view_dir = view_dir;
	ptr->light = light;
	ptr->ray = ray;
	return (ptr);
}

t_vctr	light_colors(t_light *light, t_hit hit, t_material *material,
		t_ray *ray)
{
	t_vctr	color;
	t_vctr	light_dir;
	t_vctr	view_dir;
	t_view	*view;

	light_dir = vec3_normalize(vec3_sub(*light->dir, hit.point));
	view_dir = vec3_normalize(vec3_sub(*ray->origin, hit.point));
	view = ft_view(light_dir, view_dir, light, ray);
	color = phong_lighting(view, hit.normal, material);
	free(view);
	return (color);
}

t_vctr	calculate_lighting(t_view *view, t_hit hit, t_scene *scene,
		t_material *material)
{
	t_helpers	h;
	int			in_shadow;
	t_ray		raysh;
	t_vctr		light_dir;
	t_vctr		*tm0;

	tm0 = vec_sub(*view->light->dir, hit.point);
	light_dir = vec3_normalize(*tm0);
	free(tm0);
	raysh.direction = &light_dir;
	h.tmp = vec3_add(hit.point, vec3_scale(hit.normal, 1e-4));
	raysh.origin = &h.tmp;
	h.color = light_colors(view->light, hit, material, view->ray);
	in_shadow = is_in_shaddow(scene, raysh);
	if (in_shadow)
	{
		h.color = vec3_scale(material->color, scene->alight->ratio * 0.7);
	}
	else
		fill_color(h);
	return (h.color);
}

void	fill_color(t_helpers h)
{
	h.color.x = fmin(fmax(h.color.x, 0.0), 255.0);
	h.color.y = fmin(fmax(h.color.y, 0.0), 255.0);
	h.color.z = fmin(fmax(h.color.z, 0.0), 255.0);
}

void	ft_assign_hit_plane(t_hit *hit, t_ray *ray, t_plane *plane, double t)
{
	double	den;
	t_vctr	ray_norm;

	ray_norm = vec3_normalize(*ray->direction);
	den = vec3_dot(ray_norm, *plane->normal);
	hit->hit = 1;
	hit->t = t;
	hit->point = vec3_add(*ray->origin, vec3_scale(vec3_normalize(*ray->direction), t));
	if (den < 0)
		hit->normal = *plane->normal;
	else
		hit->normal = vec3_scale(*plane->normal, -1);
}


t_hit	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit	*hit;
	t_vctr	ray_norm;
	double	den;
	t_vctr	ray_to_plane;
	double	t;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	hit->hit = 0;
	hit->t = 0;
	ray_norm = vec3_normalize(*ray->direction);
	den = vec3_dot(ray_norm, *plane->normal);
	if (fabs(den) < 1e-6)
		return (free(hit->mtrl), free(hit), NULL);
	ray_to_plane = vec3_sub(*plane->point, *ray->origin);
	t = vec3_dot(ray_to_plane, *plane->normal) / den;
	if (t < 1e-6)
		return (free(hit->mtrl), free(hit), NULL);
	ft_assign_hit_plane(hit, ray, plane, t);
	return (hit);
}
