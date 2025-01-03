/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:38:04 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/03 03:11:10 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"


int main(int ac, char **av)
{
    t_win   *data;
    t_scene *scene;

     if (ft_check_args(ac) || ft_check_extention(av[1]))
        return (1);
    scene = data_input(av[1], 1);
    if (!scene)
        return (1);
    data = malloc(sizeof(t_win));
    if (!data)
        return (1);
    data->ptr = mlx_init();
    if (!data->ptr)
        return (free(data), 1);
    data->win = mlx_new_window(data->ptr, WIDTH, HEIGHT, "miniRT");
    if (!data->win)
    {
        mlx_destroy_display(data->ptr);
        return (1);
    }
    data->img = mlx_new_image(data->ptr, WIDTH, HEIGHT);
    if (scene->pl)
    {
        while (scene->pl)
        {
           t_plane *plane = (t_plane *)(scene->pl);
            plane->mtrl = malloc(sizeof(t_material));
            plane->mtrl->color = *plane->color;
            plane->mtrl->ambient = scene->alight->ratio;
            plane->mtrl->diffuse = 0.5;
            plane->mtrl->specular = 0.5;
            plane->mtrl->shininess = 60;
            render_scene_plane(data->img, scene);
            scene->pl = scene->pl->next;
        }
    }
    if (scene->sp)
    {
        while (scene->sp)
        {
            t_sp *sphere = scene->sp;
            ft_render_sphere(&sphere, data->img, scene);
            scene->sp = scene->sp->next; 
        }
    }
    if (scene->cy)
    {
        while (scene->cy)
        {
            t_cylinder  *cyl;
            cyl = (t_cylinder *)(scene->cy);
            cyl->mtrl = malloc(sizeof(t_material));
            if (!cyl->mtrl)
            {
                printf("Failed to allocate cylinder material\n");
                free(cyl);
                free(scene);
                return (1);
            }
            cyl->mtrl->color = *cyl->color;
            cyl->mtrl->ambient = scene->alight->ratio;
            cyl->mtrl->diffuse = 0.5;
            cyl->mtrl->specular = 0.5;
            cyl->mtrl->shininess = 60;
            render_scene_cy(data->img, scene);
            scene->cy = scene->cy->next;
        }
    }
    mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
    ft_free_all(scene);
    mlx_key_hook(data->win, ft_escape_key, data);
    mlx_hook(data->win, 17, 0, ft_close, data);
    mlx_loop(data->ptr);
    return (0);
}
