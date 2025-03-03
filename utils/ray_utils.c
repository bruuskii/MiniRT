/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:17:29 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/03 17:38:09 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
	up = (t_vctr){0, 1, 0};
	right = vec3_normalize(vec3_cross(tmp, up));
	up = vec3_normalize(vec3_cross(right, tmp));
	cam->viewport_u = vec3_scale(right, -cam->viewport_width);
	cam->viewport_v = vec3_scale(up, cam->viewport_height);
}

void	ft_delta_pixels(t_cam *cam)
{
	cam->pixel_delta_u = vec3_scale(cam->viewport_u, 1.0 / (double)WIDTH);
	cam->pixel_delta_v = vec3_scale(cam->viewport_v, 1.0 / (double)HEIGHT);
}

void	ft_viewport_upper_left(t_cam *cam)
{
	t_vctr	sum;
	t_vctr	tmp;
	t_vctr	scaled_u;
	t_vctr	scaled_v;
	t_vctr	tmp1;

	tmp1 = vec3_normalize(*cam->dir);
	scaled_u = vec3_scale(cam->viewport_u, 0.5);
	scaled_v = vec3_scale(cam->viewport_v, 0.5);
	sum = vec3_add(scaled_u, scaled_v);
	tmp = vec3_add(tmp1, sum);
	cam->upper_left = vec3_sub(*cam->pos, tmp);
}
