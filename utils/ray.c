/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:22:31 by izouine           #+#    #+#             */
/*   Updated: 2025/02/17 03:56:59 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vctr	*new_vec(double x, double y, double z)
{
	t_vctr	*vctr;

	vctr = malloc(sizeof(t_vctr));
	if (!vctr)
		return (NULL);
	vctr->x = x;
	vctr->y = y;
	vctr->z = z;
	return (vctr);
}

t_vctr	*vec_add(t_vctr v1, t_vctr v2)
{
	t_vctr	*vctr;

	vctr = malloc(sizeof(t_vctr));
	if (!vctr)
		return (NULL);
	vctr->x = v1.x + v2.x;
	vctr->y = v1.y + v2.y;
	vctr->z = v1.z + v2.z;
	return (vctr);
}

t_vctr	*vec_sub(t_vctr v1, t_vctr v2)
{
	t_vctr	*vctr;

	vctr = malloc(sizeof(t_vctr));
	if (!vctr)
		return (NULL);
	vctr->x = v1.x - v2.x;
	vctr->y = v1.y - v2.y;
	vctr->z = v1.z - v2.z;
	return (vctr);
}

t_vctr	*vec_scale(t_vctr v, double d)
{
	t_vctr	*vctr;

	vctr = new_vec(v.x * d, v.y * d, v.z * d);
	if (!vctr)
		return (NULL);
	return (vctr);
}

void	ft_innit_viewports(t_cam *cam)
{
	cam->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	cam->viewport_width = 2.0 * tan(cam->fov * 0.5 * M_PI / 180);
	cam->viewport_height = cam->viewport_width / cam->aspect_ratio;
}

void	ft_viewport_vectors(t_cam *cam)
{
	t_vctr	right;
	t_vctr	up;
	t_vctr	tmp;

	tmp = vec3_normalize(*cam->dir);
	if (fabs(tmp.x) > 0.99)
		up = (t_vctr){0, 0, 1};
	else
		up = (t_vctr){0, 1, 0};
	right = vec3_normalize(vec3_cross(tmp, up));
	up = vec3_normalize(vec3_cross(right, tmp));
	cam->viewport_u = vec3_scale(up, cam->viewport_width);
	cam->viewport_v = vec3_scale(right, -cam->viewport_height);
}

void	ft_delta_pixels(t_cam *cam)
{
	cam->pixel_delta_u = vec_scale(cam->viewport_u, 1.0 / (double)WIDTH);
	cam->pixel_delta_v = vec_scale(cam->viewport_v, 1.0 / (double)HEIGHT);
}

void	ft_viewport_upper_left(t_cam *cam)
{
	t_vctr	*sum;
	t_vctr	*tmp;
	t_vctr	*scaled_u;
	t_vctr	*scaled_v;
	t_vctr	tmp1;

	tmp1 = vec3_normalize(*cam->dir);
	scaled_u = vec_scale(cam->viewport_u, 0.5);
	scaled_v = vec_scale(cam->viewport_v, 0.5);
	sum = vec_add(*scaled_u, *scaled_v);
	if (!sum)
		return ;
	tmp = vec_add(tmp1, *sum);
	if (!tmp)
		return ;
	cam->upper_left = vec_sub(*cam->pos, *tmp);
	if (!cam->upper_left)
		return ;
	free(scaled_u);
	free(scaled_v);
	free(tmp);
	free(sum);
}

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
