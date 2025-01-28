/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:52:35 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/28 09:05:23 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_world	*new_node(void *ptr, t_type type)
{
	t_world	*node;

	node = malloc(sizeof(t_world));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	ft_add_back_world(t_world **head, t_world *node)
{
	t_world	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	ft_get_far_sp(t_sp *sp, double *max, int *fl)
{
	if (sp && sp->cntr && sp->cntr->z > *max)
	{
		*max = sp->cntr->z;
		*fl = 1;
	}
}

int	get_farther_object(t_sp *sp, t_cylinder *cy, t_plane *pl, t_cone *cn)
{
	int		fl;
	double	max;

	fl = 0;
	max = INT_MIN;
	ft_get_far_sp(sp, &max, &fl);
	if (cy && cy->c_cntr && cy->c_cntr->z > max)
	{
		max = cy->c_cntr->z;
		fl = 2;
	}
	if (pl && pl->point && pl->point->z > max)
	{
		max = pl->point->z;
		fl = 3;
	}
	if (cn && cn->vertex && cn->vertex->z > max)
	{
		max = cn->vertex->z;
		fl = 4;
	}
	return (fl);
}

void	ft_free_spheres(t_sp *sp)
{
	t_sp	*tmp_next;

	while (sp)
	{
		tmp_next = (sp)->next;
		free((sp)->cntr);
		free((sp)->color);
		free(sp);
		(sp) = tmp_next;
	}
}
