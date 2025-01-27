/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:52:35 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/27 13:23:43 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_world     *new_node(void *ptr, t_type type)
{
    t_world *node;

    node = malloc(sizeof(t_world));
    if (!node)
        return (NULL);
    node->ptr = ptr;
    node->type = type;
    node->z = 0;
    node->next = NULL;
    return (node);
}

void    ft_add_back_world(t_world **head, t_world *node)
{
    t_world *tmp;
    
    if (!*head)
    {
        *head = node;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

int get_farther_object(t_sp *sp, t_cylinder *cy, t_plane *pl, t_cone *cn)
{
    int     fl;
    double max;

    fl = 0;
    max = -__DBL_MAX__;
    if (sp && sp->cntr && sp->cntr->z > max)
    {
        max = sp->cntr->z;
        fl = 1;
    }
    if (cy && cy->c_cntr && cy->c_cntr->z > max) 
    {
        max = cy->c_cntr->z;
        fl = 2;
    }
    if (pl && pl->point && pl->point->z > max) 
    {
        max = pl->point->z;
        fl = 3;
    }
    if (cn && cn->vertex && cn->vertex->z > max) 
    {
        max = cn->vertex->z;
        fl = 4;
    }
    return (fl);
    
}

void    ft_free_spheres(t_sp *sp)
{
    t_sp    *tmp_next;

    while (sp)
    {
        tmp_next = (sp)->next;
        free((sp)->cntr);
        free((sp)->color);
        free(sp);
        (sp) = tmp_next;
    }
}
t_world *ft_new_world(t_sp *sp, t_plane *pl, t_cone *cn , t_cylinder *cy)
{
    t_world    *new_world;
    t_world    *node;
    int        fl;

    new_world = NULL;
    fl = get_farther_object(sp, cy, pl, cn);
    while (fl)
    {
        if (fl == 1)
        {
            node = new_node(sp, SPHERE);
            ft_add_back_world(&new_world, node);
            sp = sp->next;
        }
        else if (fl == 2)
        {
            node = new_node(cy, CYLINDRE);
            ft_add_back_world(&new_world, node);
            cy = cy->next;
        }
        else if (fl == 3)
        {
            node = new_node(pl, PLANE);
            ft_add_back_world(&new_world, node);
            pl = pl->next;
        }
        else if (fl == 4)
        {
            node = new_node(cn, CONE);
            ft_add_back_world(&new_world, node);
            cn = cn->next;
        }
        fl = get_farther_object(sp, cy, pl, cn);
    }
    return (new_world);
}

void    ft_free_sphere(t_sp *sp)
{
    if (!sp)
        return ;
    free(sp->color);
    free(sp->cntr);
    free(sp->mtrl);
}

void    ft_free_plane(t_plane *plane)
{
    if (!plane)
        return ;
    free(plane->color);
    free(plane->point);
    free(plane->normal);
    free(plane->mtrl);
}

void    ft_free_cylinder(t_cylinder *cy)
{
    if (!cy)
        return ;
    free(cy->color);
    free(cy->c_axis);
    free(cy->c_cntr);
    free(cy->mtrl);
}

void    ft_free_cone(t_cone *cy)
{
    if (!cy)
        return ;
    free(cy->color);
    free(cy->vertex);
    free(cy->axis);
    free(cy->mtrl);
}

void	ft_free_world(t_world **world)
{
	t_world	*lt;
	t_world	*lt_next;

	lt = (*world);
	while (lt)
	{
        lt_next = lt->next;
		if (lt->type == SPHERE)
            ft_free_sphere((t_sp *)(lt->ptr));
        else if (lt->type == PLANE)
            ft_free_plane((t_plane *)lt->ptr);
        else if (lt->type == CYLINDRE)
            ft_free_cylinder((t_cylinder *)lt->ptr);
        else if (lt->type == CONE)
            ft_free_cone((t_cone *)lt->ptr);
        free(lt->ptr);
        free(lt);
        if (lt)
            lt = lt_next;
	}
    *world = NULL;
}
