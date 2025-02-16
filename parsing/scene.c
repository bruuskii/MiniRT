/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:52:57 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/30 22:00:10 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_world_to_scene(t_world **world, char **lst, int fl)
{
	t_sp		*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;

	sphere = ft_obj(lst, fl);
	plane = ft_obj_pl(lst, fl);
	cylinder = ft_obj_cy(lst, fl);
	cone = ft_cone(lst, fl);
	if (!sphere && !plane && !cylinder && !cone)
	{
		printf("%s At least one object is needed!\n", ERROR_MESSAGE);
		exit(1);
	}
	*world = ft_new_world(sphere, plane, cone, cylinder);
}
