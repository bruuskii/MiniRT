/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:11 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/30 23:41:54 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_material	*ft_material(t_scene *scene, double dif, double spec, double sh)
{
	t_material	*mtrl;

	mtrl = malloc(sizeof(t_material));
	if (!mtrl)
	{
		printf("Failed to allocate cone material\n");
		return (NULL);
	}
	mtrl->ambient = scene->alight->ratio;
	mtrl->diffuse = dif;
	mtrl->specular = spec;
	mtrl->shininess = sh;
	return (mtrl);
}

void	ft_assign_ptrs(t_scene *scene, t_world *world)
{
	t_world *tp;

	tp = world;
	while (tp)
	{
		if (tp->type == 0)
		{
			tp->txtr_dt->ptr = mlx_xpm_file_to_image(scene->data->ptr, "1.xpm", &tp->txtr_dt->width, &tp->txtr_dt->height);
			tp->txtr_dt->img_data = mlx_get_data_addr(tp->txtr_dt->ptr, &tp->txtr_dt->bpp,  &tp->txtr_dt->size_line,  &tp->txtr_dt->endian);
		}
		else if (tp->type == 1)
		{
			tp->txtr_dt->ptr = mlx_xpm_file_to_image(scene->data->ptr, "Checker.xpm", &tp->txtr_dt->width, &tp->txtr_dt->height);
			tp->txtr_dt->img_data = mlx_get_data_addr(tp->txtr_dt->ptr, &tp->txtr_dt->bpp,  &tp->txtr_dt->size_line,  &tp->txtr_dt->endian);
		}
		tp = tp->next;
	} 
}

void	ft_destroy_images(t_scene *scene, t_world *world)
{
	t_world *tp;

	tp = world;
	while (tp)
	{
		if (tp->txtr_dt->ptr)
			mlx_destroy_image(scene->data->ptr, tp->txtr_dt->ptr);
		tp = tp->next;
	}
}

void	render_scene(void *img, t_scene *scene, t_world *world)
{
	char	*img_data;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	if (!world->txtr_dt)
		return ;
	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	ft_assign_ptrs(scene, world);
	y = 0;
	if (!scene)
		return ;
	while (y < HEIGHT)
		render_scene_rows(scene, img_data, y++, world);
	ft_destroy_images(scene, world);
}

void	ft_display_scene(t_scene *scene, t_win *data)
{
	render_scene(data->img, scene, scene->world);
	ft_free_world(&scene->world);
	ft_free_all(&scene);
	free(scene);
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, ft_escape_key, data);
	mlx_hook(data->win, 17, 0, ft_close, data);
	mlx_loop(data->ptr);
}
