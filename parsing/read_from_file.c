/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:42:28 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/01 00:10:47 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int ft_check_first_param(char *s)
{
    return (!ft_strcmp(s, "A") || !ft_strcmp(s, "L") || !ft_strcmp(s, "C") || !ft_strcmp(s, "pl")|| !ft_strcmp(s, "sp") ||!ft_strcmp(s, "cy") || !ft_strcmp(s, "cn") );
}

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
        if (!ft_check_first_param(tmp[0]))
            ft_print_and_exit("Unditenfied object", 1);
        if (!ft_strcmp(tmp[0], "cn"))
        {
            if (ft_lst_count(tmp) != 7)
                ft_print_and_exit("Cone has wrong number of elements", 1);
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
        if (!ft_check_first_param(tmp[0]))
            ft_print_and_exit("Unditenfied object", 1);
        if (!ft_strcmp(tmp[0], "sp"))
        {
            int n = ft_lst_count(tmp);
            if (n < 4 || n > 8 || (n == 5 && !fl))
            {
                printf("%sSphere has incorrect parameters\n",ERROR_MESSAGE);
                exit(1);
            }
            if ((n == 5 && ft_strcmp(tmp[4], "B") && ft_strcmp(tmp[4], "C")) ||
                (n == 6 && (ft_strcmp(tmp[4], "B") || ft_strcmp(tmp[5], "C")) &&
                          (ft_strcmp(tmp[4], "C") || ft_strcmp(tmp[5], "B"))))
            {
                printf("%sSphere has wrong flag\n",ERROR_MESSAGE);
                exit(1);
            }
            if (n == 8)
            {
                if (ft_strcmp(tmp[4], "-t") && ft_strcmp(tmp[5], "img/planet.xpm")
                    && ft_strcmp(tmp[6], "-n") && ft_strcmp(tmp[7], "img/planet_normal.xpm"))
                {
                    printf("%sSphere has wrong flag\n", ERROR_MESSAGE);
                    exit(1);
                }
            }
            ptr = malloc(sizeof(t_sp));
            if (!ptr)
                return (NULL);
            ft_assign_sp(ptr, tmp + 1);
            node = ft_new(ptr);
            
            // Initialize flags
            node->fl = 0;
            node->chess = 0;
            
            // Handle n == 5 case
            if (n == 5)
            {
                if(!ft_strcmp(tmp[4], "B"))
                    node->fl = 1;
                else if (!ft_strcmp(tmp[4], "C"))
                    node->chess = 1;
            }
            // Handle n == 6 case with both flags
            else if (n == 6)
            {
                if ((!ft_strcmp(tmp[4], "B") && !ft_strcmp(tmp[5], "C")) ||
                    (!ft_strcmp(tmp[4], "C") && !ft_strcmp(tmp[5], "B")))
                {
                    node->fl = 1;
                    node->chess = 1;
                }
            }
            else if (n == 8)
            {
                if (!ft_strcmp(tmp[4], "-t") && !ft_strcmp(tmp[5], "img/planet.xpm")
                    && !ft_strcmp(tmp[6], "-n") && !ft_strcmp(tmp[7], "img/planet_normal.xpm"))
                    {
                        node->earth = 1;
                        node->texture_path = ft_strdup(tmp[5]);
                        node->normal_map_path = ft_strdup(tmp[7]);
                        load_texture_and_normal_map(node);
                    }
            }
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
        if (!ft_check_first_param(tmp[0]))
            ft_print_and_exit("Unditenfied object", 1);
        if (!ft_strcmp(tmp[0], "pl"))
        {
            if (ft_lst_count(tmp) != 4)
                ft_print_and_exit("Plane has wrong number of elements", 1);
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
        if (!tmp)
            return (NULL);
        if (!ft_check_first_param(tmp[0]))
            ft_print_and_exit("Unditenfied object", 1);
        if (!ft_strcmp(tmp[0], "cy"))
        {
            if (ft_lst_count(tmp) != 6)
                ft_print_and_exit("Cylinder has wrong number of elements", 1);
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
        if (!ft_check_first_param(tmp[0]))
            ft_print_and_exit("Unditenfied object", 1);
        if (!ft_strcmp(tmp[0], "C"))
        {
            c++;
            int n = ft_lst_count(tmp);
            if (n != 4 || c != 1)
            {
                if (c > 1)
                {
                    printf("%sOnly one camera is needed\n",ERROR_MESSAGE);
                    exit(1);
                }
                else
                {
                    printf("%sThe camera has incorrect parameters\n",ERROR_MESSAGE);
                    exit(1);
                }
            }
            ptr = malloc(sizeof(t_cam));
            ptr->type = CAM;
            ft_assign_camera(ptr, tmp);
        }
        ft_lstfree(tmp);
        i++;
    }
    if (!c)
    {
        printf("%sA camera is needed\n",ERROR_MESSAGE);
        exit (1);
    }
    return (ptr);
}

t_light   *ft_light(char **lst)
{
    int     i;
    char    **tmp;
    t_light   *node;
    t_light   *lt;
    int         c;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    c = 0;
    lt = NULL;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!tmp)
            return (NULL);
        
        if (!ft_check_first_param(tmp[0]))
            ft_print_and_exit("Unditenfied object", 1);
        if (!ft_strcmp(tmp[0], "L"))
        {
            if (ft_lst_count(tmp) != 4)
                ft_print_and_exit("Light has wrong number of elements", 1);
            node = ft_new_lt();
            ft_assign_light(node, tmp + 1);
            ft_add_back_lt(&lt, node);
            c++;
        }
        ft_lstfree(tmp);
        i++;
    }
    if (c == 0)
        ft_print_and_exit("at least one light is need", 1);
    return (lt);
}

t_alight   *ft_alight(char **lst)
{
    int         i;
    char        **tmp;
    t_alight    *node;
    int         c;

    if (!lst || !*lst)
        return (NULL);
    i = 0;
    node = NULL;
    c = 0;
    while (lst[i])
    {
        tmp = ft_fullsplit(lst[i]);
        if (!tmp)
            return (NULL);
        if (!ft_check_first_param(tmp[0]))
            ft_print_and_exit("Unditenfied object", 1);
        if (!ft_strcmp(tmp[0], "A"))
        {
            if (ft_lst_count(tmp) != 3)
                ft_print_and_exit("Light has wrong number of elements", 1);
            node = ft_a_light();
            ft_assign_alight(node, tmp + 1);
            c++;
        }
        ft_lstfree(tmp);
        i++;
    }
    if (c == 0)
        ft_print_and_exit("at least one ambient light is need", 1);
    else if (c > 1)
        if (c == 0)
        ft_print_and_exit("Only one ambient light is need", 1);
    return (node);
}
