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

	(void)world;
	final_color = ft_final_color(ray, hit, scene, hit->mtrl);
	return (final_color);
}

t_vctr	ft_check_elemts_bonus(t_ray *ray, t_hit *hit, t_world *world,
		t_scene *scene)
{
	t_vctr	final_color;

	(void)world;
	final_color = ft_final_color(ray, hit, scene, hit->mtrl);
	return (final_color);
}

void	ft_apply_color(char *img_data, int x, int y, t_vctr final_color)
{
	put_pixel_to_image(img_data, x, y, create_trgb(0, (int)final_color.x,
			(int)final_color.y, (int)final_color.z));
}

double	generate_random_double(double num)
{
	double	x;

	x = rand() / (RAND_MAX + 1.0);
	return (num + x);
}

t_vctr	vec3_multi(t_vctr v1, t_vctr v2)
{
	t_vctr	result;

	result.x = (v1.x * v2.x);
	result.y = (v1.y * v2.y);
	result.z = (v1.z * v2.z);
	return (result);
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

void	ft_render_sphere_bonus(t_hit *hit)
{
	t_sp			*sphere;
	t_vctr			*text_ptr;
	t_vctr			vec;
	t_helpers		h;
	unsigned int	color;

	sphere = (t_sp *)hit->world->ptr;
	text_ptr = vec_sub(hit->point, *sphere->cntr);
	vec = vec3_scale(*text_ptr, 1.0 / (sphere->d / 2.0));
	free(text_ptr);
	h.u = -(0.5 + atan2(vec.z, vec.x) / (2.0 * M_PI));
	h.v = (0.5 - asin(vec.y) / M_PI);
	h.tex_x = (int)(h.u * hit->world->txtr_dt->width);
	h.tex_y = (int)(h.v * hit->world->txtr_dt->height);
	if (!hit->world->txtr_dt->ptr)
		return ;
	color = *(unsigned int *)(hit->world->txtr_dt->img_data + ((h.tex_y
					* hit->world->txtr_dt->width * 4) + (h.tex_x * 4)));
	hit->mtrl->color = rgb_to_color(color);
}

void	ft_render_plane_bonus_utils(t_hit *hit, t_plane *pl, t_helpers *h)
{
	if (pl->normal->z)
	{
		h->u = hit->world->txtr_dt->width / 2.0 + (hit->point.x
				* hit->world->txtr_dt->width / M_W * 0.5);
		h->v = hit->world->txtr_dt->height / 2.0 - hit->point.y
			* hit->world->txtr_dt->height / M_H * 0.5;
	}
	if (pl->normal->x)
	{
		h->u = hit->world->txtr_dt->width / 2.0 + (hit->point.z
				* hit->world->txtr_dt->width / M_W * 0.5);
		h->v = hit->world->txtr_dt->height / 2.0 - hit->point.y
			* hit->world->txtr_dt->height / M_H * 0.5;
	}
	if (pl->normal->y)
	{
		h->u = hit->world->txtr_dt->width / 2.0 + (hit->point.z
				* hit->world->txtr_dt->width / M_W * 0.5);
		h->v = hit->world->txtr_dt->height / 2.0 - hit->point.x
			* hit->world->txtr_dt->height / M_H * 0.5;
	}
}

void	ft_render_plane_bonus(t_hit *hit)
{
	unsigned int	color;
	t_plane			*pl;
	t_helpers		h;

	pl = (t_plane *)hit->world->ptr;
	ft_render_plane_bonus_utils(hit, pl, &h);
	h.tex_x = (int)fabs(floor(h.u));
	h.tex_y = (int)fabs(floor(h.v));
	if (!hit->world->txtr_dt->ptr)
		return ;
	color = *(unsigned int *)(hit->world->txtr_dt->img_data + ((h.tex_y
					* hit->world->txtr_dt->width * 4) + (h.tex_x * 4)));
	hit->mtrl->color = rgb_to_color(color);
}

void	ft_render_cylinder_bonus(t_hit *hit)
{
	unsigned int	color;
	t_cylinder		*cy;
	t_helpers		h;

	cy = (t_cylinder *)hit->world->ptr;
	h.u = 0.5 + atan2(hit->point.x - cy->c_cntr->x, hit->point.z
			- cy->c_cntr->z) / (2.0 * M_PI);
	h.v = 1.0 - (hit->point.y - cy->c_cntr->y) / cy->height;
	if (h.u < 0)
		h.u += 1.0;
	h.v = fmax(0.0, fmin(1.0, h.v));
	h.tex_x = (int)(h.u * hit->world->txtr_dt->width);
	h.tex_y = (int)(h.v * hit->world->txtr_dt->height);
	if (!hit->world->txtr_dt->ptr)
		return ;
	color = *(unsigned int *)(hit->world->txtr_dt->img_data + ((h.tex_y
					* hit->world->txtr_dt->width * 4) + (h.tex_x * 4)));
	hit->mtrl->color = rgb_to_color(color);
}

void	ft_render_cone_bonus(t_hit *hit)
{
	unsigned int	color;
	t_cone			*cn;
	t_helpers		h;

	cn = (t_cone *)hit->world->ptr;
	h.u = 0.5 - atan2(hit->point.z - cn->vertex->z, hit->point.x
			- cn->vertex->x) / (2.0 * M_PI);
	h.v = 1.0 - (hit->point.y - cn->minm) / (cn->maxm - cn->minm);
	if (h.u < 0)
		h.u += 1.0;
	h.v = fmax(0.0, fmin(1.0, h.v));
	h.tex_x = (int)(h.u * hit->world->txtr_dt->width);
	h.tex_y = (int)(h.v * hit->world->txtr_dt->height);
	if (!hit->world->txtr_dt->ptr)
		return ;
	color = *(unsigned int *)(hit->world->txtr_dt->img_data + ((h.tex_y
					* hit->world->txtr_dt->width * 4) + (h.tex_x * 4)));
	hit->mtrl->color = rgb_to_color(color);
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

void	ft_free_scene_utils(t_scene *scene, t_hit *hit, t_ray *ray)
{
	free(ray->direction);
	free(ray);
	ft_free_cam(scene->cam);
	if (hit)
	{
		free(hit->mtrl);
		free(hit);
	}
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
		ray = get_ray(scene, (double)(x), (double)(y));
		if (!ray)
			continue ;
		hit = ft_get_hit(ray, world);
		if (hit && hit->hit)
		{
			hit->mtrl->ambient = scene->alight->ratio;
			if (hit->fl)
				ft_render_scene_bonus(hit);
			final_color = ft_check_elemts(ray, hit, world, scene);
		}
		ft_free_scene_utils(scene, hit, ray);
		ft_apply_color(img_data, x, y, final_color);
		final_color = (t_vctr){0, 0, 0};
	}
}
