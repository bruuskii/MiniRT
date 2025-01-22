/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:11 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:43:14 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_scene_cy(void *img, t_scene *scene)
{
	char	*img_data;
	int		y;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	y = 0;
	while (y < HEIGHT)
	{
		render_scene_cy_rows(scene, img_data, y, scene->cy->mtrl);
		y++;
	}
}

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

void	ft_scene_cone(t_scene *scene, t_win *data)
{
	t_cone	*con;
	t_cone	*next_cone;

	while (scene->cn)
	{
		con = (t_cone *)(scene->cn);
		next_cone = con->next;
		con->mtrl = ft_material(scene, 0.5, 0.5, 60);
		if (!con->mtrl)
		{
			printf("Failed to allocate sphere material\n");
			free(con);
			free(scene);
			return ;
		}
		con->mtrl->color = *con->color;
		render_scene_cn(data->img, scene);
		free(con->mtrl);
		free(con->axis);
		free(con->color);
		free(con->vertex);
		free(con);
		scene->cn = next_cone;
	}
}

void	ft_scene_cylinder(t_scene *scene, t_win *data)
{
	t_cylinder	*cyl;
	t_cylinder	*cy_next;

	while (scene->cy)
	{
		cyl = (t_cylinder *)(scene->cy);
		cy_next = cyl->next;
		cyl->mtrl = ft_material(scene, 0.5, 0.5, 60);
		if (!cyl->mtrl)
		{
			printf("Failed to allocate cylinder material\n");
			free(cyl);
			free(scene);
			return ;
		}
		cyl->mtrl->color = *cyl->color;
		render_scene_cy(data->img, scene);
		free(cyl->c_axis);
		free(cyl->c_cntr);
		free(cyl->color);
		if (cyl->mtrl)
			free(cyl->mtrl);
		free(cyl);
		scene->cy = cy_next;
	}
}

void	ft_scene_plane(t_scene *scene, t_win *data)
{
	t_plane	*plane;
	t_plane	*pl_next;

	while (scene->pl)
	{
		plane = (t_plane *)(scene->pl);
		pl_next = plane->next;
		plane->mtrl = ft_material(scene, 0.6, 0.6, 60);
		if (!plane->mtrl)
		{
			printf("Failed to allocate plane material\n");
			free(plane);
			free(scene);
			return ;
		}
		plane->mtrl->color = *plane->color;
		render_scene_plane(data->img, scene);
		free(plane->point);
		free(plane->normal);
		free(plane->color);
		if (plane->mtrl)
			free(plane->mtrl);
		free(plane);
		scene->pl = pl_next;
	}
}
