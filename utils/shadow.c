/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:26:43 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/02 23:37:52 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_world_shadow(t_hit **closest_hit, t_ray raysh, int fl,
		t_world *current_wrld)
{
	t_hit	*hit;

	(void)fl;
	hit = NULL;
	if (current_wrld->type == SPHERE)
		hit = intersect_sphere(&raysh, (t_sp *)current_wrld->ptr);
	else if (current_wrld->type == CYLINDRE)
		hit = intersect_cylinder(&raysh, (t_cylinder *)current_wrld->ptr);
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

int	ft_hit_world(t_world *world, t_ray raysh, int fl)
{
	t_world	*current_wrld;
	t_hit	*closest_hit;

	closest_hit = NULL;
	current_wrld = world;
	while (current_wrld)
	{
		ft_assign_world_shadow(&closest_hit, raysh, fl, current_wrld);
		current_wrld = current_wrld->next;
	}
	if (closest_hit)
	{
		free(closest_hit->mtrl);
		free(closest_hit);
		return (1);
	}
	return (0);
}

int	is_in_shadow(t_scene *scene, t_ray raysh, int fl)
{
	int	in_shadow;

	in_shadow = 0;
	if (ft_hit_world(scene->world, raysh, fl))
		in_shadow = 1;
	return (in_shadow);
}
