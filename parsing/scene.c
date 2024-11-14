/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:52:57 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/22 19:41:27 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_scene *ft_scene(char **lst)
{
    t_scene *scene;

    scene = malloc(sizeof(t_scene));
    if (!scene)
        return (NULL);
    scene->cam = ft_cam(lst);
    scene->sp = ft_obj(lst);
    scene->pl = ft_obj_pl(lst);
    scene->cy = ft_obj_cy(lst);
    scene->light = ft_light(lst);
    scene->alight = ft_alight(lst);
    ft_lstfree(lst);
    return (scene);
}

t_scene     *data_input(char *s)
{
    char    **lst;
    t_scene *scene;

    lst = ft_lines(s);
    if (!lst)
        return (NULL);
    scene = ft_scene(lst);
    if (!scene)
        return (NULL);
    return (scene);
}


void    ft_free_scene(t_scene *scene)
{
    free(scene->cam);
    free(scene->alight);
    free(scene);
}
