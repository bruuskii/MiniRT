/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:07 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/27 13:08:10 by kbassim          ###   ########.fr       */
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
	t_world *tp;

	tp = scene->world;
	while (tp)
	{
		if (tp->type == 0)
			ft_scene_sphere(scene,tp->ptr ,data);
		else if (tp->type == 1)
			ft_scene_plane(scene,tp->ptr , data);
		else if (tp->type == 2)
			ft_scene_cylinder(scene, data, tp->ptr);
		else if (tp->type == 5)
			ft_scene_cone(scene, data, tp->ptr);
		tp = tp->next;
	}
	ft_free_world(&scene->world);
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, ft_escape_key, data);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_loop(data->ptr);
}
