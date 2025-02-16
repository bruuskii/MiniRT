/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:42 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:23:41 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_sp	*ft_new(t_sp *content)
{
	t_sp	*obj;

	obj = malloc(sizeof(t_sp));
	if (!obj)
		return (NULL);
	obj->cntr = content->cntr;
	obj->color = content->color;
	obj->d = content->d;
	obj->texture = 0;
	obj->txtr_ref = NULL;
	obj->id = 0;
	obj->next = NULL;
	return (obj);
}

t_cone	*ft_new_cone(t_cone *content)
{
	t_cone	*obj;

	obj = malloc(sizeof(t_cone));
	if (!obj)
		return (NULL);
	obj->axis = content->axis;
	obj->vertex = content->vertex;
	obj->tang = content->tang;
	obj->minm = content->minm;
	obj->maxm = content->maxm;
	obj->color = content->color;
	obj->texture = 0;
	obj->txtr_ref = NULL;
	obj->next = NULL;
	return (obj);
}

t_plane	*ft_new_pl(t_plane *content)
{
	t_plane	*obj;

	obj = malloc(sizeof(t_plane));
	if (!obj)
		return (NULL);
	obj->mtrl = NULL;
	obj->point = content->point;
	obj->color = content->color;
	obj->normal = content->normal;
	obj->texture = 0;
	obj->txtr_ref = NULL;
	obj->next = NULL;
	return (obj);
}

t_cylinder	*ft_new_cy(t_cylinder *content)
{
	t_cylinder	*obj;

	obj = malloc(sizeof(t_cylinder));
	if (!obj)
		return (NULL);
	obj->mtrl = NULL;
	obj->c_axis = content->c_axis;
	obj->color = content->color;
	obj->d = content->d;
	obj->height = content->height;
	obj->c_cntr = content->c_cntr;
	obj->texture = 0;
	obj->txtr_ref = NULL;
	obj->next = NULL;
	return (obj);
}

void	ft_add_back(t_sp **objs, t_sp *node)
{
	t_sp	*tmp;

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
