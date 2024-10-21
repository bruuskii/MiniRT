/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:37:17 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/11 21:44:17 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

void    ft_assign_plane_utils(t_plane **pl, char **lst, int i)
{
    char    **tmp;

    if (!*pl || !pl)
        return ;
    if (i == 0)
    {
        tmp = ft_split(lst[i], ',');
        (*pl)->point = malloc(sizeof(t_vec3));
        if (!(*pl)->point)
            return ;
        (*pl)->point->x = ft_atodbl(tmp[0]);
        (*pl)->point->y = ft_atodbl(tmp[1]);
        (*pl)->point->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 1)
    {
        tmp = ft_split(lst[i], ',');
        (*pl)->normal = malloc(sizeof(t_vec3));
        if (!(*pl)->point)
            return ;
        (*pl)->normal->x = ft_atodbl(tmp[0]);
        (*pl)->normal->y = ft_atodbl(tmp[1]);
        (*pl)->normal->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 2)
    {
        tmp = ft_split(lst[i], ',');
        (*pl)->color = malloc(sizeof(t_vec3));
        if (!(*pl)->point)
            return ;
        (*pl)->color->color->x = ft_atoi(tmp[0]);
        (*pl)->color->color->y  = ft_atoi(tmp[1]);
        (*pl)->color->color->z = ft_atoi(tmp[2]);
        ft_lstfree(tmp);
    }
}

void    ft_assign_cy_utils(t_cylinder **cy, char **lst, int i)
{
    char    **tmp;

    if (!*cy || !cy)
        return ;
    tmp = ft_split(lst[i], ',');
    if (i == 0)
    {
        (*cy)->c_cntr = malloc(sizeof(t_vec3));
        (*cy)->c_cntr->x = ft_atodbl(tmp[0]);
        (*cy)->c_cntr->y = ft_atodbl(tmp[1]);
        (*cy)->c_cntr->z = ft_atodbl(tmp[2]);
    }
    else if (i == 1)
    {
        (*cy)->c_axis = malloc(sizeof(t_vec3));
        (*cy)->c_axis->x = ft_atodbl(tmp[0]);
        (*cy)->c_axis->y = ft_atodbl(tmp[1]);
        (*cy)->c_axis->z = ft_atodbl(tmp[2]);
    }
    else if (i == 2)
        (*cy)->d = ft_atodbl(lst[i]);
    else if (i == 3)
        (*cy)->height = ft_atodbl(lst[i]);
    else if (i == 4)
    {
        (*cy)->color = malloc(sizeof(t_material));
        (*cy)->color->color->x = ft_atoi(tmp[0]);
        (*cy)->color->color->y  = ft_atoi(tmp[1]);
        (*cy)->color->color->z = ft_atoi(tmp[2]);
    }
    ft_lstfree(tmp);
}

void    ft_assign_sp_utils(t_sphere **sp, char **lst, int i)
{
    char    **tmp;

    if (!*sp || !sp)
        return ;
    tmp = NULL;
    if (i == 0)
    {
        tmp = ft_split(lst[i], ',');
        (*sp)->center = malloc(sizeof(t_vec3));
        (*sp)->center->x = ft_atodbl(tmp[0]);
        (*sp)->center->y = ft_atodbl(tmp[1]);
        (*sp)->center->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 1)
    {
        (*sp)->radius = ft_atodbl(lst[1]);
        
    }
    else if (i == 2)
    {
        tmp = ft_split(lst[i], ',');
        (*sp)->material = malloc(sizeof(t_material));
        (*sp)->material->color = malloc(sizeof(t_vec3));
        (*sp)->material->color->x = ft_atoi(tmp[0]);
        (*sp)->material->color->y  = ft_atoi(tmp[1]);
        (*sp)->material->color->z = ft_atoi(tmp[2]);
        ft_lstfree(tmp);
    }
}

void    ft_assign_cam_utils(t_camera **cam, char **lst, int i)
{
    char    **tmp;
    
    tmp = NULL;
    if (i == 1)
    {
        tmp = ft_split(lst[i], ',');
        if (!tmp)
            return ;
        (*cam)->position = malloc(sizeof(t_vec3));
        (*cam)->position->x = ft_atodbl(tmp[0]);
        (*cam)->position->y = ft_atodbl(tmp[1]);
        (*cam)->position->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 2)
    {
        tmp = ft_split(lst[i], ',');
        if (!tmp)
            return ;
        (*cam)->direction = malloc(sizeof(t_vec3));
        (*cam)->direction->x = ft_atoi(tmp[0]);
        (*cam)->direction->y = ft_atoi(tmp[1]);
        (*cam)->direction->z = ft_atoi(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 3)
        (*cam)->fov = ft_atoi(lst[i]);
}

void    ft_assign_light_utils(t_light **lt, char **lst, int i)
{
    char    **tmp;
    
    tmp = NULL;
    if (i == 0)
    {
        tmp = ft_split(lst[i], ',');
        if (!tmp)
            return ;
        (*lt)->position = malloc(sizeof(t_vec3));
        (*lt)->position->x = ft_atodbl(tmp[0]);
        (*lt)->position->y = ft_atodbl(tmp[1]);
        (*lt)->position->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 1)
    {
        (*lt)->intensity = ft_atodbl(lst[i]);
    }
    else if (i == 2)
    {
        tmp = ft_split(lst[i], ',');
        if (!tmp)
            return ;
        (*lt)->color = malloc(sizeof(t_material));
        (*lt)->color->x = ft_atoi(tmp[0]);
        (*lt)->color->y = ft_atoi(tmp[1]);
        (*lt)->color->z = ft_atoi(tmp[2]);
        ft_lstfree(tmp);
    }
}

void    ft_assign_alight_utils(t_scene **lt, char **lst, int i)
{
    char    **tmp;

    tmp = NULL;
    if (i == 0)
        (*lt)->ratio = ft_atodbl(lst[i]);
    else if (i == 1)
    {
        tmp = ft_split(lst[i], ',');
        if (!tmp)
            return ;
        (*lt)->ambient_light = malloc(sizeof(t_material));
        (*lt)->ambient_light->x = (*lt)->ratio * ft_atoi(tmp[0]);
        (*lt)->ambient_light->y = (*lt)->ratio * ft_atoi(tmp[1]);
        (*lt)->ambient_light->z = (*lt)->ratio * ft_atoi(tmp[2]);
        ft_lstfree(tmp);
    }
}