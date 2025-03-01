/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:07 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/01 18:19:01 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vctr	ft_assign_cylinder_color(t_ray *ray, t_hit *hit, t_scene *scene)
{
	t_vctr	final_color;

	final_color = ft_final_color(ray, hit, scene, hit->mtrl);
	return (final_color);
}

void	ft_apply_color(char *img_data, int x, int y, t_vctr final_color)
{
	put_pixel_to_image(img_data, x, y, create_trgb(0, (int)final_color.x,
			(int)final_color.y, (int)final_color.z));
}

t_vctr	rgb_to_color(unsigned int color)
{
	int		r;
	int		g;
	int		b;
	t_vctr	clr;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	clr = vec3_create(r, g, b);
	return (clr);
}

void	ft_render_scene_bonus(t_hit *hit)
{
	if (hit->type == 0)
		ft_render_sphere_bonus(hit);
	else if (hit->type == 1)
		ft_render_plane_bonus(hit);
	else if (hit->type == 2)
		ft_render_cylinder_bonus(hit);
	else if (hit->type == 5)
		ft_render_cone_bonus(hit);
}

void	render_scene_rows(t_scene *scene, char *img_data, int y, t_world *world)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = -1;
	final_color = (t_vctr){0, 0, 0};
	while (++x < WIDTH)
	{
		ft_innit_cam(scene->cam);
		ray = create_ray(scene->cam, (double)(x), (double)(y));
		if (!ray)
			continue ;
		hit = ft_get_hit(ray, world);
		if (hit && hit->hit)
		{
			hit->mtrl->ambient = scene->alight->ratio;
			if (hit->fl)
				ft_render_scene_bonus(hit);
			final_color = ft_final_color(ray, hit, scene, hit->mtrl);
		}
		ft_free_scene_utils(scene, hit, ray);
		ft_apply_color(img_data, x, y, final_color);
		final_color = (t_vctr){0, 0, 0};
	}
}
