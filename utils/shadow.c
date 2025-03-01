/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:26:43 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/01 20:24:20 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_hit_world(t_world *world, t_ray raysh, int fl)
{
	t_world	*current_wrld;
	t_hit	*hit;
	t_hit	*closest_hit = NULL;

	current_wrld = world;
	while (current_wrld)
	{
		hit = NULL;
		if (current_wrld->type == SPHERE)
			hit = intersect_sphere(&raysh, (t_sp *)current_wrld->ptr);
		else if (current_wrld->type == CYLINDRE)
			hit = intersect_cylinder(&raysh, (t_cylinder *)current_wrld->ptr);
		else if (current_wrld->type == PLANE && !fl)
			hit = intersect_plane(&raysh, (t_plane *)current_wrld->ptr);
		else if (current_wrld->type == CONE)
			hit = intersect_cone(&raysh, (t_cone *)current_wrld->ptr);
		if (hit && hit->t && hit->t > 0)
		{
			if (!closest_hit || hit->t < closest_hit->t)
			{
				if (closest_hit)
					free(closest_hit);
				closest_hit = hit;
			}
			else
				free(hit);
		}
		else if (hit)
			free(hit);
		current_wrld = current_wrld->next;
	}
	if (closest_hit)
	{
		free(closest_hit->mtrl);
		free(closest_hit);
		return 1;
	}
	return 0;
}


int is_in_shadow(t_scene *scene, t_ray raysh, int fl)
{
	int in_shadow = 0;
	
	if (ft_hit_world(scene->world, raysh, fl))
		in_shadow = 1;

	return in_shadow;
}

