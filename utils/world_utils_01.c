/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:14:57 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/02 12:49:29 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_free_sphere(t_sp *sp)
{
	if (!sp)
		return ;
	if (sp->color)
		free(sp->color);
	free(sp->cntr);
}

void	ft_free_plane(t_plane *plane)
{
	if (!plane)
		return ;
	free(plane->color);
	free(plane->point);
	free(plane->normal);
}

void	ft_free_cylinder(t_cylinder *cy)
{
	if (!cy)
		return ;
	free(cy->color);
	free(cy->c_axis);
	free(cy->c_cntr);
}

void	ft_free_cone(t_cone *cy)
{
	if (!cy)
		return ;
	free(cy->color);
	free(cy->vertex);
	free(cy->axis);
}

void	ft_free_world(t_world **world)
{
	t_world	*lt;
	t_world	*lt_next;

	lt = (*world);
	while (lt)
	{
		lt_next = lt->next;
		if (lt->type == SPHERE)
			ft_free_sphere((t_sp *)(lt->ptr));
		else if (lt->type == PLANE)
			ft_free_plane((t_plane *)lt->ptr);
		else if (lt->type == CYLINDRE)
			ft_free_cylinder((t_cylinder *)lt->ptr);
		else if (lt->type == CONE)
			ft_free_cone((t_cone *)lt->ptr);
		if (lt->txtr_dt)
			free(lt->txtr_dt);
		if (lt->txtr_ref)
			free(lt->txtr_ref);
		free(lt->ptr);
		free(lt);
		if (lt)
			lt = lt_next;
	}
	*world = NULL;
}
