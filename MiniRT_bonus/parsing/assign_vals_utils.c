/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:37:17 by kbassim           #+#    #+#             */
/*   Updated: 2024/12/31 16:33:16 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void    ft_assign_plane_utils(t_plane **pl, char **lst, int i)
{
    char    **tmp;

    if (!*pl || !pl)
        return ;
    if (i == 0)
    {
        tmp = ft_split(lst[i], ',');
        (*pl)->point = malloc(sizeof(t_vctr));
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
        (*pl)->normal = malloc(sizeof(t_vctr));
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
        (*pl)->color = malloc(sizeof(t_vctr));
        if (!(*pl)->point)
            return ;
        (*pl)->color->x = ft_atodbl(tmp[0]);
        (*pl)->color->y  = ft_atodbl(tmp[1]);
        (*pl)->color->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
}

void    ft_assign_cy_utils(t_cylinder **cy, char **lst, int i)
{
    char    **tmp;

    if (!*cy || !cy)
        return ;
    if (i == 0)
    {
        tmp = ft_split(lst[i], ',');
        (*cy)->c_cntr = malloc(sizeof(t_vctr));
        (*cy)->c_cntr->x = ft_atodbl(tmp[0]);
        (*cy)->c_cntr->y = ft_atodbl(tmp[1]);
        (*cy)->c_cntr->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 1)
    {
        tmp = ft_split(lst[i], ',');
        (*cy)->c_axis = malloc(sizeof(t_vctr));
        (*cy)->c_axis->x = ft_atodbl(tmp[0]);
        (*cy)->c_axis->y = ft_atodbl(tmp[1]);
        (*cy)->c_axis->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 2)
        (*cy)->d = ft_atodbl(lst[i]);
    else if (i == 3)
        (*cy)->height = ft_atodbl(lst[i]);
    else if (i == 4)
    {
        tmp = ft_split(lst[i], ',');
        (*cy)->color = malloc(sizeof(t_vctr));
        (*cy)->color->x = ft_atodbl(tmp[0]);
        (*cy)->color->y  = ft_atodbl(tmp[1]);
        (*cy)->color->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
}

void    ft_assign_sp_utils(t_sp **sp, char **lst, int i)
{
    char    **tmp;

    if (!*sp || !sp)
        return ;
    tmp = NULL;
    if (i == 0)
    {
        tmp = ft_split(lst[i], ',');
        (*sp)->cntr = malloc(sizeof(t_vctr));
        (*sp)->cntr->x = ft_atodbl(tmp[0]);
        (*sp)->cntr->y = ft_atodbl(tmp[1]);
        (*sp)->cntr->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 1)
        (*sp)->d = ft_atodbl(lst[1]);
    else if (i == 2)
    {
        tmp = ft_split(lst[i], ',');
        (*sp)->color = malloc(sizeof(t_vctr));
        (*sp)->color->x = ft_atodbl(tmp[0]);
        (*sp)->color->y  = ft_atodbl(tmp[1]);
        (*sp)->color->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
}

void    ft_assign_cam_utils(t_cam **cam, char **lst, int i)
{
    char    **tmp;
    
    tmp = NULL;
    if (i == 1)
    {
        tmp = ft_split(lst[i], ',');
        if (!tmp)
            return ;
        (*cam)->pos = malloc(sizeof(t_vctr));
        (*cam)->pos->x = ft_atodbl(tmp[0]);
        (*cam)->pos->y = ft_atodbl(tmp[1]);
        (*cam)->pos->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 2)
    {
        tmp = ft_split(lst[i], ',');
        if (!tmp)
            return ;
        (*cam)->dir = malloc(sizeof(t_vctr));
        (*cam)->dir->x = ft_atodbl(tmp[0]);
        (*cam)->dir->y = ft_atodbl(tmp[1]);
        (*cam)->dir->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 3)
        (*cam)->fov = ft_atodbl(lst[i]);
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
        (*lt)->dir = malloc(sizeof(t_vctr));
        (*lt)->dir->x = ft_atodbl(tmp[0]);
        (*lt)->dir->y = ft_atodbl(tmp[1]);
        (*lt)->dir->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 1)
    {
        (*lt)->brightness = ft_atodbl(lst[i]);
    }
    else if (i == 2)
    {
        tmp = ft_split(lst[i], ',');
        if (!tmp)
            return ;
        (*lt)->color = malloc(sizeof(t_vctr));
        (*lt)->color->x = ft_atodbl(tmp[0]);
        (*lt)->color->y = ft_atodbl(tmp[1]);
        (*lt)->color->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
}

void    ft_assign_alight_utils(t_alight **lt, char **lst, int i)
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
        (*lt)->color = malloc(sizeof(t_vctr));
        (*lt)->color->x = ft_atodbl(tmp[0]);
        (*lt)->color->y = ft_atodbl(tmp[1]);
        (*lt)->color->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
}

void    ft_assign_cn_utils(t_cone **cn, char **lst, int i)
{
    char    **tmp;

    if (!*cn || !cn)
        return ;
    if (i == 0)
    {
        tmp = ft_split(lst[i], ',');
        (*cn)->vertex = malloc(sizeof(t_vctr));
        (*cn)->vertex->x = ft_atodbl(tmp[0]);
        (*cn)->vertex->y = ft_atodbl(tmp[1]);
        (*cn)->vertex->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 1)
    {
        tmp = ft_split(lst[i], ',');
        (*cn)->axis = malloc(sizeof(t_vctr));
        (*cn)->axis->x = ft_atodbl(tmp[0]);
        (*cn)->axis->y = ft_atodbl(tmp[1]);
        (*cn)->axis->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
    else if (i == 2)
        (*cn)->tang = ft_atodbl(lst[i]);
    else if (i == 3)
        (*cn)->minm = ft_atodbl(lst[i]);
    else if (i == 4)
        (*cn)->maxm = ft_atodbl(lst[i]);
    else if (i == 5)
    {
        tmp = ft_split(lst[i], ',');
        (*cn)->color = malloc(sizeof(t_vctr));
        (*cn)->color->x = ft_atodbl(tmp[0]);
        (*cn)->color->y = ft_atodbl(tmp[1]);
        (*cn)->color->z = ft_atodbl(tmp[2]);
        ft_lstfree(tmp);
    }
}