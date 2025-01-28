/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:20 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/28 10:44:53 by kbassim          ###   ########.fr       */
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

t_ray	*get_ray(t_scene *scene, int x, int y)
{
	double	u;
	double	v;
	t_ray	*ray;

	u = ((double)x / (WIDTH - 1));
	v = ((double)y / (HEIGHT - 1));
	ray = create_ray(scene->cam, u, v);
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

void	ft_render(t_scene *scene, char *img_data, int y, t_sp *sp)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		hit = intersect_sphere(ray, sp);
		if (!ray)
			return ;
		if (hit && hit->hit)
		{
			final_color = ft_final_color(ray, hit, scene, sp->mtrl);
			put_pixel_to_image(img_data, x, y, create_trgb(0,
					(int)final_color.x, (int)final_color.y,
					(int)final_color.z));
		}
		free(hit);
		free(ray);
		x++;
	}
}

t_hit	*ft_get_hit(t_ray *ray, t_world *world)
{
	t_hit	*hit;

	hit = NULL;
	if (world->type == 0)
		hit = intersect_sphere(ray, (t_sp *)(world->ptr));
	else if (world->type == 1)
		hit = intersect_plane(ray, (t_plane *)(world->ptr));
	else if (world->type == 2)
		hit = intersect_cylinder(ray, (t_cylinder *)(world->ptr));
	else if (world->type == 5)
		hit = intersect_cone(ray, (t_cone *)(world->ptr));
	else
	{
		free(ray);
		return (hit);
	}
	return (hit);
}
