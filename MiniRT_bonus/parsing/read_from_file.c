/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:42:28 by kbassim           #+#    #+#             */
/*   Updated: 2024/12/28 20:20:16 by kbassim          ###   ########.fr       */
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
            (*c)++;
            lst[i] = line;
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

    lst = malloc(1000 * sizeof(char *));
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

int     ft_lst_count(char **lst)
{
    int i;

    i = 0;
    while (lst[i])
        i++;
    return (i);
}

t_cone   *ft_cone(char **lst, int fl)
{
    int     i;
    t_cone    *ptr;
    char    **tmp;
    t_cone   *node;
    (void)fl;
    t_cone   *lt;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    lt = NULL;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!ft_strcmp(tmp[0], "cn"))
        {
            ptr = malloc(sizeof(t_cone));
            if (!ptr)
                return (NULL);
            ft_assign_cone(ptr, tmp + 1);
            node = ft_new_cone(ptr);
            ft_add_back_cn(&lt, node);
            free(ptr);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (lt);
}

t_sp   *ft_obj(char **lst, int fl)
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
            int n = ft_lst_count(tmp);
            if (n < 4 || n > 5 || (n == 5 && !fl))
            {
                printf("%sSphere has incorrect parameters\n",ERROR_MESSAGE);
                ft_lstfree(tmp);
                ft_lstfree(lst);
                return (NULL);
            }
            if (n == 5 && ft_strcmp(tmp[4], "B") && ft_strcmp(tmp[4], "C"))
            {
                printf("%sSphere has wrong flag\n",ERROR_MESSAGE);
                ft_lstfree(tmp);
                ft_lstfree(lst);
                return (NULL);
            }
            ptr = malloc(sizeof(t_sp));
            if (!ptr)
                return (NULL);
            ft_assign_sp(ptr, tmp + 1);
            node = ft_new(ptr);
            if (n == 5)
            {
                node->fl = 1;
                if (!ft_strcmp(tmp[4], "C"))
                {
                    node->chess = strdup("C");  // Allocate and copy "C"
                }
            }
            else
                node->fl = 0;
            ft_add_back(&lt, node);
            free(ptr);
        }
        ft_lstfree(tmp);
        i++;
    }
    return (lt);
}

t_plane  *ft_obj_pl(char **lst, int fl)
{
    int     i;
    t_plane    *ptr;
    char    **tmp;
    t_plane   *node;
    t_plane   *lt;

    (void) fl;
    
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
    int     c;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    ptr = NULL;
    c = 0;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!tmp)
            return (NULL);
        if (!ft_strcmp(tmp[0], "C"))
        {
            c++;
            int n = ft_lst_count(tmp);
            if (n != 4 || c != 1)
            {
                if (c > 1)
                {
                    printf("%sOnly one camera is needed\n",ERROR_MESSAGE);
                    ft_lstfree(tmp);
                    return (NULL);
                }
                else
                {
                    
                    ft_lstfree(tmp);
                    return (printf("%sThe camera has incorrect parameters\n",ERROR_MESSAGE), NULL);
                }
            }
            ptr = malloc(sizeof(t_cam));
            ptr->type = CAM;
            ft_assign_camera(ptr, tmp);
        }
        ft_lstfree(tmp);
        i++;
    }
    // if (!c)
    // {
    //     printf("%sA camera is needed\n",ERROR_MESSAGE);
    //     ft_lstfree(tmp);
    //     //ft_lstfree(lst);
    //     return (NULL);
    // }
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
    node = NULL;
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