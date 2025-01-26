/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:26:43 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/25 00:48:11 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_sphere_param(t_scene *scene, t_ray raysh)
{
	t_sp	*current_sphere;
	t_hit	*shadow_hit;

	current_sphere = scene->sp;
	while (current_sphere)
	{
		shadow_hit = intersect_sphere(&raysh, current_sphere);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			free(shadow_hit);
			return (1);
		}
		if (shadow_hit)
			free(shadow_hit);
		current_sphere = current_sphere->next;
	}
	return (0);
}

int	ft_hit_plane(t_scene *scene, t_ray raysh)
{
	t_plane	*current_plane;
	t_hit	*shadow_hit;

	current_plane = scene->pl;
	while (current_plane)
	{
		shadow_hit = intersect_plane(&raysh, current_plane);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			free(shadow_hit);
			return (1);
		}
		if (shadow_hit)
			free(shadow_hit);
		current_plane = current_plane->next;
	}
	return (0);
}

int	ft_hit_cone(t_scene *scene, t_ray raysh)
{
	t_cone	*current_cone;
	t_hit	*shadow_hit;

	current_cone = scene->cn;
	while (current_cone)
	{
		shadow_hit = intersect_cone(&raysh, current_cone);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			free(shadow_hit);
			return (1);
		}
		if (shadow_hit)
			free(shadow_hit);
		current_cone = current_cone->next;
	}
	return (0);
}

int	ft_hit_cy(t_scene *scene, t_ray raysh)
{
	t_cylinder	*current_cy;
	t_hit		*shadow_hit;

	current_cy = scene->cy;
	while (current_cy)
	{
		shadow_hit = intersect_cylinder(&raysh, current_cy);
		if (shadow_hit && shadow_hit->hit && shadow_hit->t)
		{
			free(shadow_hit);
			return (1);
		}
		if (shadow_hit)
			free(shadow_hit);
		current_cy = current_cy->next;
	}
	return (0);
}

int	is_in_shaddow(t_scene *scene, t_ray raysh)
{
	int	in_shadow;

	in_shadow = 0;
	if (ft_sphere_param(scene, raysh))
		in_shadow = 1;
	if (ft_hit_plane(scene, raysh))
		in_shadow = 1;
	if (ft_hit_cy(scene, raysh))
		in_shadow = 1;
	if (ft_hit_cone(scene, raysh))
		in_shadow = 1;
	return (in_shadow);
}
