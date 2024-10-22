/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:42 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/22 19:43:11 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_obj   *ft_new(void *content)
{
    t_obj       *obj;
    t_material  *mtrl;

    mtrl = malloc(sizeof(t_material));
    if (!mtrl)
        return (NULL);
    obj = malloc(sizeof(t_obj));
    if (!obj)
        return (NULL);
    obj->obj = content;
    obj->mtrl = mtrl;
    obj->mtrl->ambient = 0.1;
    obj->mtrl->diffuse = 0.5;
    obj->mtrl->shininess = 10;
    obj->mtrl->specular = 0.5;
    obj->next = NULL;
    return (obj);
}

void   ft_add_back(t_obj **objs, t_obj *node)
{
    t_obj *tmp;

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