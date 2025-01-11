/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:42 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/09 17:19:15 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_sp   *ft_new(t_sp *content)
{
    t_sp       *obj;

    obj = malloc(sizeof(t_sp));
    if (!obj)
        return (NULL);
    obj->cntr = content->cntr;
    obj->color = content->color;
    obj->d = content->d;
    obj->chess = 0;
    obj->id = 0;
    obj->next = NULL;
    return (obj);
}

t_cone   *ft_new_cone(t_cone *content)
{
    t_cone       *obj;

    obj = malloc(sizeof(t_cone));
    if (!obj)
        return (NULL);
    obj->axis = content->axis;
    obj->vertex = content->vertex;
    obj->tang = content->tang;
    obj->minm = content->minm;
    obj->maxm = content->maxm;
    obj->color = content->color;
    obj->next = NULL;
    return (obj);
}

t_plane   *ft_new_pl(t_plane *content)
{
    t_plane       *obj;

    obj = malloc(sizeof(t_plane));
    if (!obj)
        return (NULL);
    obj->mtrl = NULL;
    obj->point = content->point;
    obj->color = content->color;
    obj->normal = content->normal;
    obj->next = NULL;
    return (obj);
}

t_cylinder   *ft_new_cy(t_cylinder *content)
{
    t_cylinder       *obj;

    obj = malloc(sizeof(t_cylinder));
    if (!obj)
        return (NULL);
    obj->mtrl = NULL;
    obj->c_axis = content->c_axis;
    obj->color = content->color;
    obj->d = content->d;
    obj->height = content->height;
    obj->c_cntr = content->c_cntr;
    obj->next = NULL;
    return (obj);
}

void   ft_add_back(t_sp **objs, t_sp *node)
{
    t_sp *tmp;

    if (!*objs)
    {
        *objs = node;
        return ;
    }
    tmp = *objs;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

void   ft_add_back_pl(t_plane **objs, t_plane *node)
{
    t_plane *tmp;

    if (!*objs)
    {
        *objs = node;
        return ;
    }
    tmp = *objs;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

void   ft_add_back_cy(t_cylinder **objs, t_cylinder *node)
{
    t_cylinder *tmp;

    if (!*objs)
    {
        *objs = node;
        return ;
    }
    tmp = *objs;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

t_light   *ft_new_lt()
{
    t_light   *lt;

    lt = malloc(sizeof(t_light));
    if (!lt)
        return (NULL);
    lt->dir = NULL;
    lt->brightness = 0.0;
    lt->color = NULL;
    lt->type = LIGHT;
    lt->next = NULL;
    return (lt);
}

t_alight   *ft_a_light()
{
    t_alight   *lt;

    lt = malloc(sizeof(t_alight));
    if (!lt)
        return (NULL);
    lt->ratio = 0.0;
    lt->color = NULL;
    lt->type = ALIGHT;
    return (lt);
}

void   ft_add_back_lt(t_light **objs, t_light *node)
{
    t_light *tmp;

    if (!*objs)
    {
        *objs = node;
        return ;
    }
    tmp = *objs;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

void   ft_add_back_cn(t_cone **cn, t_cone *node)
{
    t_cone *tmp;

    if (!*cn)
    {
        *cn = node;
        return ;
    }
    tmp = *cn;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}
