/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:49:08 by izouine           #+#    #+#             */
/*   Updated: 2025/02/06 07:26:22 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_checker(t_hit *hit, t_vctr original_normal)
{
	double	bump_intensity;
	double	noise_x;
	double	noise_y;
	double	noise_z;
	t_vctr	noise_offset;

	bump_intensity = 0.1;
	noise_x = fmod(sin(hit->point.x * 10), 1.0);
	noise_y = fmod(cos(hit->point.y * 10), 1.0);
	noise_z = fmod(tan(hit->point.z * 10), 1.0);
	noise_offset = (t_vctr){noise_x * bump_intensity, noise_y * bump_intensity,
		noise_z * bump_intensity};
	hit->normal = vec3_normalize(vec3_add(original_normal, noise_offset));
}

t_vctr	vec3_negate(t_vctr v)
{
	return ((t_vctr){-v.x, -v.y, -v.z});
}

void	ft_checker_plane(t_hit *hit, t_vctr original_normal)
{
	double	bump_intensity;
	double	noise_x;
	double	noise_z;
	t_vctr	noise_offset;

	bump_intensity = 1.5;
	noise_x = fmod(sin(hit->point.x * 10), 1.0);
	noise_z = fmod(cos(hit->point.z * 10), 1.0);
	noise_offset = (t_vctr){noise_x * bump_intensity, 0, noise_z
		* bump_intensity};
	hit->normal = vec3_normalize(vec3_add(original_normal, noise_offset));
}

// t_vctr	calculate_chess_pattern(t_hit hit)
// {
// 	t_helpers	helper;

// 	helper.u = 0.5 + atan2(hit.normal.z, hit.normal.x) / (2 * M_PI);
// 	helper.v = 0.5 - asin(hit.normal.y) / M_PI;
// 	return ((t_vctr){0,0,0});
// }

void	fill_dhiya(t_helpers h)
{
	h.color.x = fmin(fmax(h.color.x, 0.0), 255.0);
	h.color.y = fmin(fmax(h.color.y, 0.0), 255.0);
	h.color.z = fmin(fmax(h.color.z, 0.0), 255.0);
}
