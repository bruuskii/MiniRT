/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:07 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/26 23:44:01 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_scene_sphere(t_scene *scene, void *ptr, t_win *data)
{
	t_sp	*sphere;

	sphere = (t_sp *)(ptr);
	sphere->mtrl = ft_material(scene, 0.5, 0.5, 60);
	if (!sphere->mtrl)
	{
		printf("Failed to allocate sphere material\n");
		free(sphere);
		free(scene);
		return ;
	}
	sphere->mtrl->color = *sphere->color;
	render_scene(data->img, scene, sphere);
}

void	ft_display_scene(t_scene *scene, t_win *data)
{
	while (scene->world)
	{
		if (scene->world->type == 0)
			ft_scene_sphere(scene,scene->world->ptr ,data);
		else if (scene->world->type == 1)
			ft_scene_plane(scene,scene->world->ptr , data);
		else if (scene->world->type == 2)
			ft_scene_cylinder(scene, data, scene->world->ptr);
		else if (scene->world->type == 5)
			ft_scene_cone(scene, data, scene->world->ptr);
		scene->world = scene->world->next;
	}
	ft_free_all(&scene);
	free(scene);
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, ft_escape_key, data);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_loop(data->ptr);
}
