/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:52:57 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/26 23:45:00 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void swapNodes(t_sp* a, t_sp* b) 
{
	
    double temp_d = a->d;
    t_material* temp_mtrl = a->mtrl;
    t_vctr* temp_cntr = a->cntr;
    t_vctr* temp_color = a->color;
    int temp_fl = a->fl;
    int temp_chess = a->chess;
    int temp_id = a->id;

    a->d = b->d;
    a->mtrl = b->mtrl;
    a->cntr = b->cntr;
    a->color = b->color;
    a->fl = b->fl;
    a->chess = b->chess;
    a->id = b->id;

    b->d = temp_d;
    b->mtrl = temp_mtrl;
    b->cntr = temp_cntr;
    b->color = temp_color;
    b->fl = temp_fl;
    b->chess = temp_chess;
    b->id = temp_id;
}

void swap_planes(t_plane* a, t_plane* b) 
{
    t_material* temp_mtrl = a->mtrl;
    t_vctr* temp_point = a->point;
    t_vctr* temp_normal = a->normal;
	t_vctr* temp_color = a->color;

    a->mtrl = b->mtrl;
    a->point = b->point;
    a->color = b->color;
    a->normal = b->normal;

    b->mtrl = temp_mtrl;
    b->point = temp_point;
    b->color = temp_color;
    b->normal = temp_normal;
}

void swap_cylinders(t_cylinder* a, t_cylinder* b) 
{
    t_material* temp_mtrl = a->mtrl;
    t_vctr* temp_axis = a->c_axis;
    t_vctr* temp_center = a->c_cntr;
	t_vctr* temp_color = a->color;
	double	temp_d = a->d;
	double	temp_height = a->height;

    a->mtrl = b->mtrl;
    a->c_axis = b->c_axis;
	a->c_cntr = b->c_cntr;
    a->color = b->color;
	a->d = b->d;
	a->height = b->height;

    b->mtrl = temp_mtrl;
    b->c_axis = temp_axis;
	b->c_cntr = temp_center;
    b->color = temp_color;
	b->d = temp_d;
	b->height = temp_height;
}

void swap_cones(t_cone* a, t_cone* b) 
{
    t_material* temp_mtrl = a->mtrl;
    t_vctr* temp_axis = a->axis;
    t_vctr* temp_vertex = a->vertex;
	t_vctr* temp_color = a->color;
	double	temp_maxm = a->maxm;
	double	temp_minm = a->minm;
	double	temp_tang = a->tang;

    a->mtrl = b->mtrl;
    a->axis = b->axis;
	a->vertex = b->vertex;
    a->color = b->color;
	a->tang = b->tang;
	a->minm = b->minm;
    a->maxm = b->maxm;

    b->mtrl = temp_mtrl;
    b->axis = temp_axis;
	b->vertex = temp_vertex;
    b->color = temp_color;
	b->tang = temp_tang;
	b->minm = temp_minm;
	b->maxm = temp_maxm;
}

void sort_cylinder(t_cylinder* head) 
{
    int swapped;
    t_cylinder* ptr;
    t_cylinder* last = NULL;

    while (swapped) 
	{
        swapped = 0;
        ptr = head;

        while (ptr->next != last) 
		{
            if (ptr->c_cntr->z > ptr->next->c_cntr->z) 
			{
                swap_cylinders(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
}

void sort_sphere(t_sp* head) 
{
    int swapped;
    t_sp* ptr;
    t_sp* last = NULL;

    while (swapped) 
	{
        swapped = 0;
        ptr = head;

        while (ptr->next != last) 
		{
            if (ptr->cntr->z > ptr->next->cntr->z) 
			{
                swapNodes(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
}

void sort_plane(t_plane* head) 
{
    int swapped;
    t_plane* ptr;
    t_plane* last = NULL;

    while (swapped) 
	{
        swapped = 0;
        ptr = head;
        while (ptr->next != last) 
		{
            if (!ptr->normal->z && ptr->next->normal->z) 
			{
                swap_planes(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
}

void sort_cone(t_cone* head) 
{
    int swapped;
    t_cone* ptr;
    t_cone* last = NULL;

    while (swapped) 
	{
        swapped = 0;
        ptr = head;
        while (ptr->next != last) 
		{
            if (!ptr->vertex->z && ptr->next->vertex->z) 
			{
                swap_cones(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
}

t_scene	*ft_scene(char **lst, int fl)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->cam = ft_cam(lst);
	scene->sp = ft_obj(lst, fl);
    if (scene->sp)
	    sort_sphere(scene->sp);
	scene->pl = ft_obj_pl(lst, fl);
    if (scene->pl)
	    sort_plane(scene->pl);
	scene->cy = ft_obj_cy(lst);
    if (scene->cy)
	    sort_cylinder(scene->cy);
	if (!scene->sp && !scene->pl && !scene->cy && !scene->cn)
	{
		printf("%s At least one object is needed!\n", ERROR_MESSAGE);
		exit(1);
	}
	scene->cn = ft_cone(lst, fl);
    if (scene->cn)
	    sort_cone(scene->cn);
	scene->world = ft_new_world(scene->sp, scene->pl, scene->cn, scene->cy);
	scene->light = ft_light(lst);
	scene->alight = ft_alight(lst);
	ft_lstfree(lst);
	return (scene);
}

t_scene	*data_input(char *s, int fl)
{
	char	**lst;
	t_scene	*scene;

	lst = ft_lines(s);
	if (!lst)
		return (NULL);
	scene = ft_scene(lst, fl);
	if (!scene)
		return (NULL);
	return (scene);
}

void	ft_free_scene(t_scene *scene)
{
	free(scene->cam);
	free(scene->alight);
	free(scene);
}
