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
	if (world->type == 0)
		world->txtr_dt->ptr = mlx_xpm_file_to_image(scene->data->ptr, "Checker.xpm", &world->txtr_dt->width, &world->txtr_dt->height);
	if (world->txtr_dt->ptr)
		world->txtr_dt->img_data = mlx_get_data_addr(world->txtr_dt->ptr, &world->txtr_dt->bpp,  &world->txtr_dt->size_line,  &world->txtr_dt->endian);
	y = 0;
	if (!scene)
		return ;
	while (y < HEIGHT)
	{
		render_scene_rows(scene, img_data, y, world);
		y++;
	}
	if (world->txtr_dt->ptr)
		mlx_destroy_image(scene->data->ptr, world->txtr_dt->ptr);
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
