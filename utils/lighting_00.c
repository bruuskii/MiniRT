/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:16:49 by izouine           #+#    #+#             */
/*   Updated: 2025/01/22 22:16:59 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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

double	vec3_length(t_vctr vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vctr	vec3_multiply(t_vctr v1, t_vctr v2)
{
	t_vctr	result;

	result.x = (v1.x * v2.x) / 255.0;
	result.y = (v1.y * v2.y) / 255.0;
	result.z = (v1.z * v2.z) / 255.0;
	return (result);
}

t_vctr	light_colors(t_light *light, t_hit hit, t_material *material,
		t_ray *ray)
{
	t_vctr	color;
	t_vctr	light_dir;
	t_vctr	view_dir;
	t_view	*view;

	light_dir = vec3_normalize(vec3_sub(*light->dir, hit.point));
	view_dir = vec3_normalize(vec3_sub(ray->origin, hit.point));
	view = ft_view(light_dir, view_dir, light, ray);
	color = phong_lighting(view, hit.normal, material);
	free(view);
	return (color);
}
