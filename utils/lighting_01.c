/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:15:39 by izouine           #+#    #+#             */
/*   Updated: 2025/03/03 00:37:24 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vctr	ft_reflected_dir(t_vctr normal, t_view *view)
{
	t_vctr	reflect_dir;
	t_vctr	tmp;
	double	coeff;

	coeff = 2 * vec3_dot(normal, view->light_dir);
	tmp = vec3_scale(normal, coeff);
	reflect_dir = vec3_sub(tmp, view->light_dir);
	return (vec3_normalize(reflect_dir));
}

t_vctr	phong_lighting(t_view *view, t_vctr normal, t_material *material)
{
	double	ambient;
	double	diffuse;
	double	specular;
	t_vctr	color;
	t_vctr	reflect_dir;

	reflect_dir = ft_reflected_dir(normal, view);
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

void	ft_assign_light_dir_sh(t_vctr *light_dir, t_view *view, t_hit hit)
{
	t_vctr	tm0;

	tm0 = vec3_sub(*view->light->dir, hit.point);
	*light_dir = vec3_normalize(tm0);
}

t_vctr	calculate_lighting(t_view *view, t_hit hit, t_scene *scene,
		t_material *material)
{
	t_helpers	h;
	int			in_shadow;
	t_ray		raysh;
	t_vctr		light_dir;
	int			fl;

	ft_assign_light_dir_sh(&light_dir, view, hit);
	raysh.direction = &light_dir;
	h.tmp = vec3_add(hit.point, hit.normal);
	raysh.origin = &h.tmp;
	h.color = light_colors(view->light, hit, material, view->ray);
	fl = get_fl(scene->world, view->light);
	in_shadow = is_in_shadow(scene, raysh, fl);
	if (in_shadow)
		h.color = vec3_scale(material->color, scene->alight->ratio
				* view->light->brightness);
	fill_color(h);
	return (h.color);
}
