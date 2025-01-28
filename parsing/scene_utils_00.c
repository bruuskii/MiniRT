/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:19:41 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/27 23:20:05 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_scene	*ft_scene(char **lst, int fl)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->cam = ft_cam(lst);
	ft_assign_world_to_scene(&scene->world, lst, fl);
	scene->light = ft_light(lst);
	scene->alight = ft_alight(lst);
	ft_lstfree(lst);
	return (scene);
}

t_scene	*data_input(char *s, int fl)
{
	char	**lst;
	t_scene	*scene;

	lst = ft_lines(s);
	if (!lst)
		return (NULL);
	scene = ft_scene(lst, fl);
	if (!scene)
		return (NULL);
	return (scene);
}

void	ft_free_scene(t_scene *scene)
{
	free(scene->cam);
	free(scene->alight);
	free(scene);
}
