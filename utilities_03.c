/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:18 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/26 14:38:14 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_scene_cn_rows(t_scene *scene, char *img_data, int y,
		t_cone *cone)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		hit = intersect_cone(ray, cone);
		if (!ray)
			return ;
		if (hit && hit->hit)
		{
			final_color = ft_final_color(ray, hit, scene, cone->mtrl);
			put_pixel_to_image(img_data, x, y, create_trgb(0,
					(int)final_color.x, (int)final_color.y,
					(int)final_color.z));
		}
		free(hit);
		free(ray);
		x++;
	}
}

void	render_scene_cn(void *img, t_scene *scene, t_cone *cone)
{
	char	*img_data;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	if (!scene)
		return ;
	while (y < HEIGHT)
	{
		render_scene_cn_rows(scene, img_data, y, cone);
		y++;
	}
}

void	render_scene_plane_rows(t_scene *scene, char *img_data, int y,
		t_plane *pl)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		hit = intersect_plane(ray, pl);
		if (!ray)
			return ;
		if (hit && hit->hit)
		{
			final_color = ft_final_color(ray, hit, scene, pl->mtrl);
			put_pixel_to_image(img_data, x, y, create_trgb(0,
					(int)final_color.x, (int)final_color.y,
					(int)final_color.z));
		}
		free(hit);
		free(ray);
		x++;
	}
}

void	render_scene_plane(void *img, t_scene *scene, t_plane *pl)
{
	char	*img_data;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	while (y < HEIGHT)
	{
		render_scene_plane_rows(scene, img_data, y, pl);
		y++;
	}
}

void	render_scene_cy_rows(t_scene *scene, char *img_data, int y,
		t_cylinder *cy)
{
	int		x;
	t_ray	*ray;
	t_hit	*hit;
	t_vctr	final_color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(scene, x, y);
		hit = intersect_cylinder(ray, cy);
		if (!ray)
			return ;
		if (hit && hit->hit)
		{
			final_color = ft_final_color(ray, hit, scene, cy->mtrl);
			put_pixel_to_image(img_data, x, y, create_trgb(0,
					(int)final_color.x, (int)final_color.y,
					(int)final_color.z));
		}
		free(hit);
		free(ray);
		x++;
	}
}
