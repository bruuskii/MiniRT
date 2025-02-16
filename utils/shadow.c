/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:26:43 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/31 15:26:40 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_hit_world(t_world *world, t_ray raysh)
{
	t_world	*current_wrld;
	t_hit	*shadow_hit;

	current_wrld = world;
	while (current_wrld)
	{
		shadow_hit = NULL;
		if (current_wrld->type == SPHERE)
			shadow_hit = intersect_sphere(&raysh, (t_sp *)current_wrld->ptr);
		else if (current_wrld->type == CYLINDRE)
			shadow_hit = intersect_cylinder(&raysh,
					(t_cylinder *)current_wrld->ptr);
		else if (current_wrld->type == PLANE)
			shadow_hit = intersect_plane(&raysh, (t_plane *)current_wrld->ptr);
		else if (current_wrld->type == CONE)
			shadow_hit = intersect_cone(&raysh, (t_cone *)current_wrld->ptr);
		if (shadow_hit && shadow_hit->t)
			return (free(shadow_hit->mtrl), free(shadow_hit), 1);
		if (shadow_hit)
			free(shadow_hit);
		current_wrld = current_wrld->next;
	}
	return (0);
}

int	is_in_shaddow(t_scene *scene, t_ray raysh)
{
	int	in_shadow;

	in_shadow = 0;
	if (ft_hit_world(scene->world, raysh))
		in_shadow = 1;
	return (in_shadow);
}
