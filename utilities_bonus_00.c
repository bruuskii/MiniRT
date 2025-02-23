/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus_00.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:28:59 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/23 11:34:24 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
