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

t_vctr	ft_bump(t_vctr color)
{
	t_vctr	tmp;

	tmp.x = (color.x / 255.0) * 2 - 1.0;
	tmp.y = (color.y / 255.0) * 2 - 1.0;
	tmp.z = (color.z / 255.0) * 2 - 1.0;
	return (tmp);
}

t_vctr	get_normal_vector(t_vctr normal, t_vctr color)
{
	t_vctr	tang;
	t_vctr	btang;
	t_vctr	norml;
	t_vctr	bump;

	normal = vec3_normalize(normal);
	if (fabs(normal.x) > 0.9)
		tang = (t_vctr){0, 1.0, 0};
	else if (fabs(normal.y) > 0.9)
		tang = (t_vctr){1.0, 0, 0};
	else
		tang = (t_vctr){0.0, 0.0, 1.0};
	bump = ft_bump(color);
	btang = vec3_cross(tang, normal);
	tang = vec3_cross(btang, normal);
	norml.x = normal.x + bump.x * tang.x + bump.x * btang.x;
	norml.y = normal.y + bump.y * tang.y + bump.y * btang.y;
	norml.z = normal.z + bump.z * tang.z + bump.z * btang.z;
	norml = vec3_normalize(norml);
	return (norml);
}

t_vctr	vec3_multi(t_vctr v1, t_vctr v2)
{
	t_vctr	result;

	result.x = (v1.x * v2.x);
	result.y = (v1.y * v2.y);
	result.z = (v1.z * v2.z);
	return (result);
}

t_vctr	color_to_vctr(int col)
{
	t_vctr			color;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (col >> 16) & 0xFF;
	g = (col >> 8) & 0xFF;
	b = col & 0xFF;
	color = vec3_create(r, g, b);
	return (color);
}

void	render_chess_sphere(t_hit *hit)
{
	t_sp			*sphere;
	t_vctr			vec;
	unsigned int	color;
	t_vctr			*text_ptr;
	t_txtr			txtr;

	sphere = (t_sp *)hit->world->ptr;
	text_ptr = vec_sub(hit->point, *sphere->cntr);
	vec = vec3_scale(*text_ptr, 1.0 / (sphere->d / 2.0));
	free(text_ptr);
	txtr.u = -(0.5 + atan2(vec.z, vec.x) / (2.0 * M_PI));
	txtr.v = (0.5 - asin(vec.y) / M_PI);
	txtr.tex_x = (int)(txtr.u * hit->world->txtr_dt->width);
	txtr.tex_y = (int)(txtr.v * hit->world->txtr_dt->height);
	if (!hit->world->txtr_dt->ptr)
		return ;
	color = *(unsigned int *)(hit->world->txtr_dt->img_data
			+ ((txtr.tex_y * hit->world->txtr_dt->width * 4) + (txtr.tex_x
					* 4)));
	hit->mtrl->color = color_to_vctr(color);
}

void	render_chess_plane_innit(t_txtr *txtr, t_hit *hit, t_plane *pl)
{
	if (pl->normal->z)
	{
		txtr->u = hit->world->txtr_dt->width / 2.0 + (hit->point.x
				* hit->world->txtr_dt->width / M_W * 0.5);
		txtr->v = hit->world->txtr_dt->height / 2.0 - hit->point.y
			* hit->world->txtr_dt->height / M_H * 0.5;
	}
	if (pl->normal->x)
	{
		txtr->u = hit->world->txtr_dt->width / 2.0 + (hit->point.z
				* hit->world->txtr_dt->width / M_W * 0.5);
		txtr->v = hit->world->txtr_dt->height / 2.0 - hit->point.y
			* hit->world->txtr_dt->height / M_H * 0.5;
	}
	if (pl->normal->y)
	{
		txtr->u = hit->world->txtr_dt->width / 2.0 + (hit->point.z
				* hit->world->txtr_dt->width / M_W * 0.5);
		txtr->v = hit->world->txtr_dt->height / 2.0 - hit->point.x
			* hit->world->txtr_dt->height / M_H * 0.5;
	}
}

void	render_chess_plane(t_hit *hit)
{
	t_plane			*pl;
	t_txtr			txtr;
	unsigned int	color;

	pl = (t_plane *)hit->world->ptr;
	render_chess_plane_innit(&txtr, hit, pl);
	txtr.tex_x = (int)fabs(floor(txtr.u));
	txtr.tex_y = (int)fabs(floor(txtr.v));
	if (!hit->world->txtr_dt->ptr)
		return ;
	color = *(unsigned int *)(hit->world->txtr_dt->img_data
			+ ((txtr.tex_y * hit->world->txtr_dt->width * 4) + (txtr.tex_x
					* 4)));
	hit->mtrl->color = color_to_vctr(color);
}

void	render_chess_cy(t_hit *hit)
{
	t_cylinder		*cy;
	t_txtr			txtr;
	unsigned int	color;

	cy = (t_cylinder *)hit->world->ptr;
	txtr.u = 0.5 + atan2(hit->point.x - cy->c_cntr->x, hit->point.z
			- cy->c_cntr->z) / (2.0 * M_PI);
	txtr.v = (hit->point.y - cy->c_cntr->y) / cy->height;
	txtr.u = fmod(txtr.u, 1.0);
	if (txtr.u < 0)
		txtr.u += 1.0;
	txtr.v = fmax(0.0, fmin(1.0, txtr.v));
	txtr.tex_x = (int)(txtr.u * hit->world->txtr_dt->width);
	txtr.tex_y = (int)(txtr.v * hit->world->txtr_dt->height);
	if (!hit->world->txtr_dt->ptr)
		return ;
	color = *(unsigned int *)(hit->world->txtr_dt->img_data
			+ ((txtr.tex_y * hit->world->txtr_dt->width * 4) + (txtr.tex_x
					* 4)));
	hit->mtrl->color = color_to_vctr(color);
}

void	render_chess_cn(t_hit *hit)
{
	t_cone			*cn;
	t_txtr			txtr;
	unsigned int	color;

	cn = (t_cone *)hit->world->ptr;
	txtr.u = 0.5 + atan2(hit->point.z - cn->vertex->z, hit->point.x
			- cn->vertex->x) / (2.0 * M_PI);
	txtr.v = 1.0 - (hit->point.y - cn->minm) / (cn->maxm - cn->minm);
	txtr.u = fmod(txtr.u, 1.0);
	if (txtr.u < 0)
		txtr.u += 1.0;
	txtr.v = fmax(0.0, fmin(1.0, txtr.v));
	txtr.tex_x = (int)floor(txtr.u * hit->world->txtr_dt->width);
	txtr.tex_y = (int)floor(txtr.v * hit->world->txtr_dt->height);
	txtr.tex_x = (int)fmax(0, txtr.tex_x);
	txtr.tex_y = (int)fmax(0, txtr.tex_y);
	if (!hit->world->txtr_dt->ptr)
		return ;
	color = *(unsigned int *)(hit->world->txtr_dt->img_data
			+ ((txtr.tex_y * hit->world->txtr_dt->width * 4) + (txtr.tex_x
					* 4)));
	hit->mtrl->color = color_to_vctr(color);
}

void	ft_render_bonus(t_hit *hit)
{
	if (hit->type == 0)
		render_chess_sphere(hit);
	else if (hit->type == 1)
		render_chess_plane(hit);
	else if (hit->type == 2)
		render_chess_cy(hit);
	else if (hit->type == 5)
		render_chess_cn(hit);
}

void	ft_render_free(t_hit *hit, t_ray *ray, t_scene *scene)
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

t_ray		*render_rays(t_scene *scene, int x, int y)
{
	t_ray			*ray;

	ft_innit_cam(scene->cam);
	ray = get_ray(scene, (double)(x), (double)(y));
	if (!ray)
		return (NULL);
	return (ray);	
}

void	render_scene_rows(t_scene *scene, char *img_data, int y, t_world *world)
{
	int				x;
	t_hit			*hit;
	t_vctr			final_color;
	t_ray			*ray;

	x = -1;
	while (++x < WIDTH)
	{
		ray = render_rays(scene, x, y);
		if (!ray)
			continue ;
		hit = ft_get_hit(ray, world);
		if (hit && hit->hit)
		{
			hit->mtrl->ambient = scene->alight->ratio;
			if (hit->fl)
				ft_render_bonus(hit);
			final_color = ft_check_elemts(ray, hit, world, scene);
		}
		ft_render_free(hit, ray, scene);
		ft_apply_color(img_data, x, y, vec3_scale(final_color, 1.0));
	}
}
