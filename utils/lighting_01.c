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

t_vctr	phong_lighting(t_view *view, t_vctr normal, t_material *material)
{
	double	ambient;
	double	diffuse;
	double	specular;
	t_vctr	color;
	t_vctr	reflect_dir;

	 reflect_dir = vec3_sub(vec3_scale(normal, 2 * vec3_dot(normal,
	 				view->light_dir)), view->light_dir);
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
	t_ray       *raysh;
	t_vctr 		tmp;

	raysh = malloc(sizeof(t_ray));
	raysh->direction = view->light->dir;
	tmp = hit.point;
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
