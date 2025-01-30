/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:07 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/30 23:18:56 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vctr	ft_assign_cylinder_color(t_ray *ray, t_hit *hit, t_world *world,
		t_scene *scene)
{
	t_vctr	final_color;

	(void)world;
	final_color = ft_final_color(ray, hit, scene, hit->mtrl);
	return (final_color);
}

t_vctr	ft_check_elemts(t_ray *ray, t_hit *hit, t_world *world, t_scene *scene)
{
	t_vctr	final_color;

	if (world->type == 0)
	{
		final_color = ft_final_color(ray, hit, scene, hit->mtrl);
	}
	else if (world->type == 1)
	{
		final_color = ft_final_color(ray, hit, scene, hit->mtrl);
	}
	else if (world->type == 2)
		return (ft_assign_cylinder_color(ray, hit, world, scene));
	return (final_color);
}

t_vctr	ft_check_elemts_bonus(t_ray *ray, t_hit *hit, t_world *world,
		t_scene *scene)
{
	t_vctr	final_color;

	if (world->type == 5)
	{
		final_color = ft_final_color(ray, hit, scene, hit->mtrl);
	}
	return (final_color);
}

void	ft_apply_color(char *img_data, int x, int y, t_vctr final_color)
{
	put_pixel_to_image(img_data, x, y, create_trgb(0, (int)final_color.x,
			(int)final_color.y, (int)final_color.z));
}

void	render_scene_rows(t_scene *scene, char *img_data, int y, t_world *world)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = -1;
	while (++x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		if (!ray)
			continue ;
		hit = ft_get_hit(ray, world, scene);
		if (hit && hit->hit)
		{
			if (world->type == 5)
				ft_check_elemts_bonus(ray, hit, world, scene);
			else
				final_color = ft_check_elemts(ray, hit, world, scene);
			ft_apply_color(img_data, x, y, final_color);
		}
		free(ray);
		if (hit)
			free(hit->mtrl);
		free(hit);
	}
}
