/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:22:31 by izouine           #+#    #+#             */
/*   Updated: 2025/03/04 13:53:15 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_delta_pixels(t_cam *cam)
{
	cam->pixel_delta_u = vec3_scale(cam->viewport_u, 1.0 / (double)WIDTH);
	cam->pixel_delta_v = vec3_scale(cam->viewport_v, 1.0 / (double)HEIGHT);
}

void	ft_pixel_offset(t_cam *cam)
{
	t_vctr	result;
	t_vctr	scaled_result;

	result = vec3_add(cam->pixel_delta_u, cam->pixel_delta_v);
	scaled_result = vec3_scale(result, 0.5);
	cam->pixel_offset = vec3_add(cam->bottom_left, scaled_result);
}

void	ft_innit_cam(t_cam *cam)
{
	ft_innit_viewports(cam);
	ft_viewport_vectors(cam);
	ft_delta_pixels(cam);
	ft_viewport_bottom_left(cam);
	ft_pixel_offset(cam);
}

t_ray	*create_ray(t_cam *cam, double x, double y)
{
	t_ray	*ray;
	t_vctr	pixel_center;
	t_vctr	scaled_x;
	t_vctr	tmp;
	t_vctr	scaled_y;

	if (!cam)
		return (NULL);
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	scaled_x = vec3_scale(cam->pixel_delta_u, x);
	scaled_y = vec3_scale(cam->pixel_delta_v, y);
	tmp = vec3_add(scaled_x, scaled_y);
	pixel_center = vec3_add(cam->pixel_offset, tmp);
	ray->origin = cam->pos;
	ray->direction = malloc(sizeof(t_vctr));
	if (!ray->direction)
		return (NULL);
	*ray->direction = vec3_sub(*cam->pos, pixel_center);
	return (ray);
}
