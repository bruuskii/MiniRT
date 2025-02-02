/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:22:31 by izouine           #+#    #+#             */
/*   Updated: 2025/01/22 22:22:32 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_u_and_v(t_cam *cam)
{
	t_vctr	u_vec;
	t_vctr	v_vec;

	u_vec = (t_vctr){0, 1, 0};
	v_vec = vec3_cross(vec3_normalize(vec3_scale(*(cam->dir), -1)), u_vec);
	u_vec = vec3_cross(v_vec, vec3_normalize(vec3_scale(*(cam->dir), -1)));
	cam->u_vec = u_vec;
	cam->v_vec = v_vec;
}

void	get_view_ports(t_cam *cam)
{
	cam->aspect_ratio = (double)WIDTH / HEIGHT;
	cam->viewport_height = 2.0 * tan(cam->fov * 0.5 * M_PI / 180.0);
	cam->viewport_width = cam->aspect_ratio * cam->viewport_height;
}

void	get_horiz_vert(t_cam *cam)
{
	ft_u_and_v(cam);
	get_view_ports(cam);
	cam->hor = vec3_scale(cam->u_vec, cam->aspect_ratio * cam->viewport_height);
	cam->ver = vec3_scale(cam->v_vec, cam->viewport_height);
}

void	upper_left(t_cam *cam)
{
	t_vctr	s_hor;
	t_vctr	s_ver;
	t_vctr	s_cam_dir;

	s_hor = vec3_scale(cam->hor, 0.5);
	s_ver = vec3_scale(cam->ver, 0.5);
	s_cam_dir = vec3_normalize(vec3_scale(*(cam->dir), -1));
	cam->upper_left = vec3_sub(*(cam->pos), vec3_add(s_hor, vec3_add(s_ver, s_cam_dir)));
}

t_ray	*create_ray(t_cam *cam, double u, double v)
{
	t_ray	*ray;
	t_vctr	vctr;
	t_vctr	s_h;
	t_vctr	s_v;

	if (!cam)
		return (NULL);
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	get_horiz_vert(cam);
	s_h = vec3_scale(cam->hor, u);
	s_v = vec3_scale(cam->ver, v);
	ray->origin = *(cam->pos);
	vctr = vec3_sub(vec3_add(cam->upper_left, vec3_add(s_h, s_v)), *(cam->pos));
	ray->direction = vec3_normalize(vctr);
	return (ray);
}
