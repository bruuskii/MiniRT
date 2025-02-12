/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:07 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/07 22:52:37 by kbassim          ###   ########.fr       */
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

	final_color = (t_vctr){0,0,0};
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

	final_color = (t_vctr){0,0,0};
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

// void	render_scene_rows(t_scene *scene, char *img_data, int y, t_world *world)
// {
// 	int		x;
// 	t_ray	*ray;
// 	t_hit	*hit;
// 	t_vctr	final_color;

// 	x = -1;
// 	while (++x < WIDTH)
// 	{
// 		ft_innit_cam(scene->cam);
// 		ray = get_ray(scene, (double)x, (double)y);
// 		if (!ray)
// 			continue ;
// 		hit = ft_get_hit(ray, world, scene);
// 		if (hit && hit->hit)
// 		{
// 			if (world->type == 5)
// 				ft_check_elemts_bonus(ray, hit, world, scene);
// 			else
// 				final_color = ft_check_elemts(ray, hit, world, scene);
// 			ft_apply_color(img_data, x, y, final_color);
// 		}
// 		free(ray->direction), free(ray), ft_free_cam(scene->cam);
// 		if (hit)
// 			free(hit->mtrl), free(hit);
// 	}
// }

double generate_random_double(double num)
{
    double x;

    x = rand() / (RAND_MAX + 1.0);
    return (num + x);
}

void	render_scene_rows(t_scene *scene, char *img_data, int y, t_world *world)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;
	double	count;
	t_vctr col;

	x = -1;
	count = 0.0;
	final_color = (t_vctr){0, 0, 0};
	while (++x < WIDTH)
	{
		ft_innit_cam(scene->cam);
		ray = get_ray(scene, (double) x, (double)y);
		if (!ray)
			continue ;
		hit = ft_get_hit(ray, world, scene);
		if (hit && hit->hit)
		{
			count += 1.0;
			if (world->type == 5)
				ft_check_elemts_bonus(ray, hit, world, scene);
			else
			{
				if (hit && hit->type == 0)
				{
					t_sp	*sphere;

					sphere = (t_sp *)world->ptr; 
					t_vctr vec = vec3_scale(vec3_sub(hit->point, *sphere->cntr), 1.0 / (sphere->d / 2.0)); 
					float u = 0.5 + atan2(vec.z, vec.x) / (2.0 * M_PI);
					float v = 0.5 - asin(vec.y) / M_PI ;
					int	 tex_x = (int)(u * world->txtr_dt->width);
					int	 tex_y = (int)(v * world->txtr_dt->height);
					if (!world->txtr_dt->ptr)
						return ;
					int color = *(unsigned int *)(world->txtr_dt->img_data + (tex_y * world->txtr_dt->width + tex_x) * 4);
					unsigned char r = (color >> 16) & 0xFF;
					unsigned char g = (color >> 8) & 0xFF;  
					unsigned char b = color & 0xFF;       
					col = (t_vctr){(double)r , (double)g , (double)b};
					hit->mtrl->color = col;
					final_color = ft_check_elemts(ray, hit, world, scene);
				}
				else
					final_color = vec3_add(final_color,ft_check_elemts(ray, hit, world, scene));
				ft_apply_color(img_data, x, y, final_color);
			}
		}
		free(ray->direction), free(ray), ft_free_cam(scene->cam);
		if (hit)
			free(hit->mtrl), free(hit);
		final_color = (t_vctr){0, 0, 0};
		count = 0.0;
	}
}
