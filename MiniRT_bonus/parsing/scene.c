/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:52:57 by kbassim           #+#    #+#             */
/*   Updated: 2024/12/28 20:22:12 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_scene *ft_scene(char **lst, int fl)
{
    t_scene *scene;

    scene = malloc(sizeof(t_scene));
    if (!scene)
        return (NULL);
    scene->cam = ft_cam(lst);
    // if (!scene->cam)
        // return (ft_free_all(scene), NULL);
    scene->sp = ft_obj(lst, fl);
    // if (!scene->sp)
        // return (ft_free_all(scene), NULL);
    scene->pl = ft_obj_pl(lst, fl);
    // if (!scene->pl)
        // return (ft_free_all(scene), NULL);
    scene->cy = ft_obj_cy(lst);
    // if (!scene->cy)
        // return (ft_free_all(scene), NULL);
    scene->cn = ft_cone(lst, fl);
    // if (!scene->cn)
        // return (ft_free_all(scene), NULL);
    scene->light = ft_light(lst);
    // if (!scene->light)
        // return (ft_free_all(scene), NULL);
    scene->alight = ft_alight(lst);
    // if (!scene->alight)
        // return (ft_free_all(scene), NULL);
    //ft_lstfree(lst);
    return (scene);
}

t_scene     *data_input(char *s, int fl)
{
    char    **lst;
    t_scene *scene;

    lst = ft_lines(s);
    if (!lst)
        return (NULL);
    scene = ft_scene(lst, fl);
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
