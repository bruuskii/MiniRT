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

#include "../includes/minirt_bonus.h"

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

t_obj   *ft_obj(char **lst)
{
    int     i;
    void    *ptr;
    char    **tmp;
    t_obj   *node;
    t_obj   *lt;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    lt = NULL;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!tmp)
            return (NULL);
        if (!ft_strcmp(tmp[0], "pl"))
        {
            ptr = malloc(sizeof(t_plane));
            if (!ptr)
                return (NULL);
            node = ft_new((t_plane *)ptr);
            node->type = PLANE;
            ft_assign_plane((t_plane *)ptr, tmp + 1);
            ft_add_back(&lt, node);
        }
        else if (!ft_strcmp(tmp[0], "cy"))
        {
            ptr = malloc(sizeof(t_cylinder));
            if (!ptr)
                return (NULL);
            node = ft_new((t_cylinder *)ptr);
            node->type = CYLINDRE;
            ft_assign_cy((t_cylinder *)ptr, tmp + 1);
            ft_add_back(&lt, node);
        }
        else if (!ft_strcmp(tmp[0], "sp"))
        {
            ptr = malloc(sizeof(t_sphere));
            if (!ptr)
                return (NULL);
            node = ft_new((t_sphere *)ptr);
            node->type = SPHERE;
            ft_assign_sp((t_sphere *)ptr, tmp + 1);
            ft_add_back(&lt, node);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (lt);
}

t_camera   *ft_cam(char **lst)
{
    int     i;
    t_camera   *ptr;
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
            ptr = malloc(sizeof(t_camera));
            ptr->type = CAM;
            ft_assign_camera(ptr, tmp);
        }
        //ft_lstfree(tmp);
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

t_scene   *ft_alight(char **lst)
{
    int         i;
    char        **tmp;
    t_scene    *node;

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