/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:42:28 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/11 09:35:00 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void    ft_line_utils(int *c, int fd, char **lst)
{
    int     i;
    char    *line;

    i = 0;
    while ((line = get_next_line(fd)))
    {
        if (!ft_strcmp(line, "") || !ft_strcmp(line, "\n"))
        {
            free(line);
            continue;
        }
        else
        {
            lst[i] = line;
            (*c)++;
        }
        i++;
    }
    lst[i] = NULL;
}

char    **ft_lines(char *filename)
{
    int     fd;
    char    **lst;
    int     c;

    lst = malloc(20 * sizeof(char *));
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error when openning file\n");
        free(lst);
        return (NULL);
    }
    c = 0;
    ft_line_utils(&c, fd, lst);
    close(fd);
    if (c == 0)
    {
        printf("Empty file\n");
        free(lst);
        return (NULL);
    }
    return (lst);
}

t_sp   *ft_obj(char **lst)
{
    int     i;
    t_sp    *ptr;
    char    **tmp;
    t_sp   *node;
    t_sp   *lt;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    lt = NULL;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!ft_strcmp(tmp[0], "sp"))
        {
            ptr = malloc(sizeof(t_sp));
            if (!ptr)
                return (NULL);
            ft_assign_sp(ptr, tmp + 1);
            node = ft_new(ptr);
            ft_add_back(&lt, node);
            free(ptr);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (lt);
}

t_plane  *ft_obj_pl(char **lst)
{
    int     i;
    t_plane    *ptr;
    char    **tmp;
    t_plane   *node;
    t_plane   *lt;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    lt = NULL;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!ft_strcmp(tmp[0], "pl"))
        {
            ptr = malloc(sizeof(t_plane));
            if (!ptr)
                return (NULL);
            ft_assign_plane(ptr, tmp + 1);
            node = ft_new_pl(ptr);
            ft_add_back_pl(&lt, node);
            free(ptr);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (lt);
}


t_cylinder  *ft_obj_cy(char **lst)
{
    int             i;
    t_cylinder   *ptr;
    char         **tmp;
    t_cylinder   *node;
    t_cylinder   *lt;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    lt = NULL;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!ft_strcmp(tmp[0], "cy"))
        {
            ptr = malloc(sizeof(t_cylinder));
            if (!ptr)
                return (NULL);
            ft_assign_cy(ptr, tmp + 1);
            node = ft_new_cy(ptr);
            ft_add_back_cy(&lt, node);
            free(ptr);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (lt);
}

t_cam   *ft_cam(char **lst)
{
    int     i;
    t_cam   *ptr;
    char    **tmp;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    ptr = NULL;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!tmp)
            return (NULL);
        if (!ft_strcmp(tmp[0], "C"))
        {
            ptr = malloc(sizeof(t_cam));
            ptr->type = CAM;
            ft_assign_camera(ptr, tmp);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (ptr);
}

t_light   *ft_light(char **lst)
{
    int     i;
    char    **tmp;
    t_light   *node;
    t_light   *lt;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    lt = NULL;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!tmp)
            return (NULL);
        if (!ft_strcmp(tmp[0], "L"))
        {
            node = ft_new_lt();
            ft_assign_light(node, tmp + 1);
            ft_add_back_lt(&lt, node);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (lt);
}

t_alight   *ft_alight(char **lst)
{
    int         i;
    char        **tmp;
    t_alight    *node;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!tmp)
            return (NULL);
        if (!ft_strcmp(tmp[0], "A"))
        {
            node = ft_a_light();
            ft_assign_alight(node, tmp + 1);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (node);
}