/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:22:31 by izouine           #+#    #+#             */
/*   Updated: 2025/02/23 11:18:25 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_pixel_offset(t_cam *cam)
{
	t_vctr	*result;
	t_vctr	*scaled_result;

	result = vec_add(*cam->pixel_delta_u, *cam->pixel_delta_v);
	if (!result)
		return ;
	scaled_result = vec_scale(*result, 0.5);
	if (!scaled_result)
		return ;
	cam->pixel_offset = vec_add(*cam->upper_left, *scaled_result);
	free(result);
	free(scaled_result);
}

void	ft_innit_cam(t_cam *cam)
{
	ft_innit_viewports(cam);
	ft_viewport_vectors(cam);
	ft_delta_pixels(cam);
	ft_viewport_upper_left(cam);
	ft_pixel_offset(cam);
}

void	ft_free_cam(t_cam *cam)
{
	if (cam->pixel_delta_u)
		free(cam->pixel_delta_u);
	if (cam->pixel_delta_v)
		free(cam->pixel_delta_v);
	if (cam->pixel_offset)
		free(cam->pixel_offset);
	if (cam->upper_left)
		free(cam->upper_left);
}

t_ray	*create_ray(t_cam *cam, double x, double y)
{
	t_ray	*ray;
	t_vctr	*pixel_center;
	t_vctr	*scaled_x;
	t_vctr	*tmp;
	t_vctr	*scaled_y;

	if (!cam)
		return (NULL);
	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	scaled_x = vec_scale(*cam->pixel_delta_v, x);
	scaled_y = vec_scale(*cam->pixel_delta_u, y);
	tmp = vec_add(*scaled_x, *scaled_y);
	pixel_center = vec_add(*cam->pixel_offset, *tmp);
	ray->origin = cam->pos;
	ray->direction = vec_sub(*pixel_center, *cam->pos);
	free(pixel_center);
	free(scaled_x);
	free(tmp);
	free(scaled_y);
	return (ray);
}
