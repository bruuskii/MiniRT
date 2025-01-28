/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:52:57 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/27 23:24:56 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	sort_cylinder(t_cylinder *head)
{
	int			swapped;
	t_cylinder	*ptr;
	t_cylinder	*last;

	last = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next != last)
		{
			if (ptr->c_cntr->z > ptr->next->c_cntr->z)
			{
				swap_cylinders(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last = ptr;
	}
}

void	sort_sphere(t_sp *head)
{
	int		swapped;
	t_sp	*ptr;
	t_sp	*last;

	last = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next != last)
		{
			if (ptr->cntr->z > ptr->next->cntr->z)
			{
				ft_swap_circle(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last = ptr;
	}
}

void	sort_plane(t_plane *head)
{
	int		swapped;
	t_plane	*ptr;
	t_plane	*last;

	last = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next != last)
		{
			if (!ptr->normal->z && (ptr->point->z))
			{
				swap_planes(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last = ptr;
	}
}

void	sort_cone(t_cone *head)
{
	int		swapped;
	t_cone	*ptr;
	t_cone	*last;

	last = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next != last)
		{
			if (ptr->vertex->z > ptr->next->vertex->z)
			{
				swap_cones(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last = ptr;
	}
}

void	ft_assign_world_to_scene(t_world **world, char **lst, int fl)
{
	t_sp		*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;

	sphere = ft_obj(lst, fl);
	if (sphere)
		sort_sphere(sphere);
	plane = ft_obj_pl(lst, fl);
	if (plane)
		sort_plane(plane);
	cylinder = ft_obj_cy(lst);
	if (cylinder)
		sort_cylinder(cylinder);
	cone = ft_cone(lst, fl);
	if (cone)
		sort_cone(cone);
	if (!sphere && !plane && !cylinder && !cone)
	{
		printf("%s At least one object is needed!\n", ERROR_MESSAGE);
		exit(1);
	}
	*world = ft_new_world(sphere, plane, cone, cylinder);
}
