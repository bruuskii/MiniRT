/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:15:39 by izouine           #+#    #+#             */
/*   Updated: 2025/03/01 20:21:56 by kbassim          ###   ########.fr       */
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

int check_planes(t_plane *pl, t_light *light)
{
	int fl;

	fl = 0;
	if (!pl || !light || !pl->normal || !pl->point || !light->dir)
		return (0);
	if (pl && pl->normal->x != 0)
	{
		if (light->dir->x > 0 && pl->point->x > 0 && light->dir->x > pl->point->x)
			fl = 1;
		if (light->dir->x < 0  && fabs(light->dir->x) > fabs(pl->point->x))
			fl = 1; 
	}
	return (fl);
}

int	get_fl(t_world *world, t_light *light)
{
	t_world	*current_wrld;
	t_plane *pl;
	int		fl;
	t_vctr	sub0;
	int inf;

	current_wrld = world;
	fl = 0;
	inf = 0;
	while (current_wrld)
	{
		if (current_wrld->type == PLANE)
		{
			pl = (t_plane *)current_wrld->ptr;
			inf = check_planes(pl, light);
			if (pl && pl->normal && pl->point)
			{
				sub0 = vec3_sub(*light->dir, *pl->point);
				if (vec3_dot(sub0, *pl->normal) < 0 && !inf)
				{
					fl = 1;
					break ;
				}	
				else
					fl = 0;
			}
		}
		current_wrld = current_wrld->next;
	}
	return (fl);
}

t_vctr	calculate_lighting(t_view *view, t_hit hit, t_scene *scene,
		t_material *material)
{
	t_helpers	h;
	int			in_shadow;
	t_ray		raysh;
	t_vctr		light_dir;
	t_vctr		*tm0;
	int			fl;

	tm0 = vec_sub(*view->light->dir, hit.point);
	light_dir = vec3_normalize(*tm0);
	free(tm0);
	raysh.direction = &light_dir;
	h.tmp = vec3_add(hit.point, hit.normal);
	raysh.origin = &h.tmp;
	h.color = light_colors(view->light, hit, material, view->ray);
	fl = get_fl(scene->world, view->light);
	in_shadow = is_in_shadow(scene, raysh, fl);
	if (in_shadow)
		h.color = vec3_scale(material->color, scene->alight->ratio * view->light->brightness);
	fill_color(h);
	return (h.color);
}
