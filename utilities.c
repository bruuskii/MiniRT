/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:07 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:43:09 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_scene_sphere(t_scene *scene, t_win *data)
{
	t_sp	*sphere;
	t_sp	*sp_next;

	while (scene->sp)
	{
		sphere = scene->sp;
		sp_next = sphere->next;
		sphere->mtrl = ft_material(scene, 0.5, 0.5, 60);
		if (!sphere->mtrl)
		{
			printf("Failed to allocate sphere material\n");
			free(sphere);
			free(scene);
			return ;
		}
		sphere->mtrl->color = *sphere->color;
		render_scene(data->img, scene);
		free(sphere->cntr);
		free(sphere->color);
		if (sphere->mtrl)
			free(sphere->mtrl);
		free(sphere);
		scene->sp = sp_next;
	}
}

void	ft_display_scene(t_scene *scene, t_win *data)
{
	if (scene->pl)
		ft_scene_plane(scene, data);
	if (scene->sp)
		ft_scene_sphere(scene, data);
	if (scene->cy)
		ft_scene_cylinder(scene, data);
	if (scene->cn)
		ft_scene_cone(scene, data);
	ft_free_all(&scene);
	free(scene);
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, ft_escape_key, data);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_loop(data->ptr);
}
