/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:26:43 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/04 15:08:44 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_world_shadow(t_hit **closest_hit, t_ray raysh,
		t_world *current_wrld)
{
	t_hit	*hit;

	hit = NULL;
	if (current_wrld->type == SPHERE)
		hit = intersect_sphere(&raysh, (t_sp *)current_wrld->ptr);
	else if (current_wrld->type == CYLINDRE)
		hit = intersect_cylinder(&raysh, (t_cylinder *)current_wrld->ptr);
	else if (current_wrld->type == PLANE)
		hit = intersect_plane(&raysh, (t_plane *)current_wrld->ptr);
	else if (current_wrld->type == CONE)
		hit = intersect_cone(&raysh, (t_cone *)current_wrld->ptr);
	if (hit && hit->t && hit->t > 0)
	{
		if (!*closest_hit || hit->t < (*closest_hit)->t)
		{
			if (*closest_hit)
				ft_free_hit_elems(*closest_hit);
			*closest_hit = hit;
		}
		else
			ft_free_hit_elems(hit);
	}
	else if (hit)
		ft_free_hit_elems(hit);
}

int	check_closest_hit_shadow(t_hit *c_hit, long distance)
{
	if (c_hit && c_hit->t > 0 && c_hit->t < distance)
	{
		free(c_hit->mtrl);
		free(c_hit);
		return (1);
	}
	if (c_hit)
	{
		free(c_hit->mtrl);
		free(c_hit);
	}
	return (0);
}

int	intersect_world_with_raysh(t_scene *scene, t_ray raysh, double distance)
{
	t_hit	*closest_hit;
	t_world	*current_wrld;

	closest_hit = NULL;
	current_wrld = scene->world;
	while (current_wrld)
	{
		ft_assign_world_shadow(&closest_hit, raysh, current_wrld);
		current_wrld = current_wrld->next;
	}
	if (check_closest_hit_shadow(closest_hit, distance))
		return (1);
	return (0);
}

int	is_in_shadow(t_scene *scene, t_hit hit, t_light *light)
{
	t_ray	raysh;
	t_vctr	light_dir;
	double	light_distance;
	t_vctr	origin;

	light_dir = vec3_sub(*light->dir, hit.point);
	light_distance = vec3_length(light_dir);
	origin = vec3_add(hit.point, vec3_scale(hit.normal, 1e-6));
	light_dir = vec3_normalize(light_dir);
	raysh.origin = &origin;
	raysh.direction = &light_dir;
	if (intersect_world_with_raysh(scene, raysh, light_distance))
		return (1);
	return (0);
}
