/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:16:05 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/28 08:57:45 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_add_sphere_to_world(t_sp **sp, t_world **new_world)
{
	t_world	*node;

	node = new_node(*sp, SPHERE);
	ft_add_back_world(new_world, node);
	*sp = (*sp)->next;
}

void	ft_add_cylinder_to_world(t_cylinder **cy, t_world **new_world)
{
	t_world	*node;

	node = new_node(*cy, CYLINDRE);
	ft_add_back_world(new_world, node);
	*cy = (*cy)->next;
}

void	ft_add_plane_to_world(t_plane **pl, t_world **new_world)
{
	t_world	*node;

	node = new_node(*pl, PLANE);
	ft_add_back_world(new_world, node);
	*pl = (*pl)->next;
}

void	ft_add_cone_to_world(t_cone **cn, t_world **new_world)
{
	t_world	*node;

	node = new_node(*cn, CONE);
	ft_add_back_world(new_world, node);
	*cn = (*cn)->next;
}

t_world	*ft_new_world(t_sp *sp, t_plane *pl, t_cone *cn, t_cylinder *cy)
{
	t_world	*new_world;
	int		fl;

	new_world = NULL;
	fl = get_farther_object(sp, cy, pl, cn);
	while (fl)
	{
		if (fl == 1)
			ft_add_sphere_to_world(&sp, &new_world);
		else if (fl == 2)
			ft_add_cylinder_to_world(&cy, &new_world);
		else if (fl == 3)
			ft_add_plane_to_world(&pl, &new_world);
		else if (fl == 4)
			ft_add_cone_to_world(&cn, &new_world);
		fl = get_farther_object(sp, cy, pl, cn);
	}
	return (new_world);
}
