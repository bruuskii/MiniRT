/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:49:08 by izouine           #+#    #+#             */
/*   Updated: 2025/03/02 23:35:15 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_render_sphere_bonus(t_hit *hit)
{
	t_sp			*sphere;
	t_vctr			text_ptr;
	t_vctr			vec;
	t_helpers		h;
	unsigned int	color;

	sphere = (t_sp *)hit->world->ptr;
	text_ptr = vec3_sub(hit->point, *sphere->cntr);
	vec = vec3_scale(text_ptr, 1.0 / (sphere->d / 2.0));
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
