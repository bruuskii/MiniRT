/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:42:28 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/14 01:55:10 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_check_first_param(char *s)
{
	return (!ft_strcmp(s, "A") || !ft_strcmp(s, "L") || !ft_strcmp(s, "C")
		|| !ft_strcmp(s, "pl") || !ft_strcmp(s, "sp") || !ft_strcmp(s, "cy")
		|| !ft_strcmp(s, "cn"));
}

int	 ft_count_line(char *filename, int fd)
{
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("%sError when openning file\n", ERROR_MESSAGE), exit (1), -1);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (!ft_strcmp(line, "") || !ft_strcmp(line, "\n"))
		{
			i++;
			free(line);
			continue ;
		}
		else
		{
			free(line);
			i++;
		}
	}
	close(fd);
	if (i > 2147483647)
		return (printf("%sNumber of lines has exceeded INT_MAX\n", ERROR_MESSAGE), exit(1), -1);
	return (i);
}

void	ft_line_utils(int *c, int fd, char **lst)
{
	int		i;
	char	*line;

	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (!ft_strcmp(line, "") || !ft_strcmp(line, "\n"))
		{
			free(line);
			continue ;
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

char	**ft_lines(char *filename)
{
	int		fd;
	char	**lst;
	int		c;

	fd = open(filename, O_RDONLY);
	lst = malloc((ft_count_line(filename, fd) + 1) * sizeof(char *));
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
	ft_count_line(filename, fd);
	return (lst);
}

int	ft_lst_count(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		i++;
	return (i);
}

t_cone	*ft_cone(char **lst, int fl)
{
	int		i;
	t_cone	*ptr;
	char	**tmp;
	t_cone	*node;
	t_cone	*lt;

	(void)fl;
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

t_sp	*ft_obj(char **lst, int fl)
{
	int		i;
	t_sp	*ptr;
	char	**tmp;
	t_sp	*node;
	t_sp	*lt;
	int		j;
	int		n;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	j = 0;
	lt = NULL;
	while (lst[i])
	{
		tmp = ft_fullsplit(lst[i]);
		if (!ft_check_first_param(tmp[0]))
			ft_print_and_exit("Unditenfied object", 1);
		if (!ft_strcmp(tmp[0], "sp"))
		{
			n = ft_lst_count(tmp);
			if (n < 4 || n > 6 || ((n == 5 || n == 6) && !fl))
			{
				printf("%sSphere has incorrect parameters\n", ERROR_MESSAGE);
				exit(1);
			}
			if ((n == 5 && ft_strcmp(tmp[4], "B") && ft_strcmp(tmp[4], "C"))
				|| (n == 6 && (ft_strcmp(tmp[4], "B") || ft_strcmp(tmp[5], "C"))
					&& (ft_strcmp(tmp[4], "C") || ft_strcmp(tmp[5], "B"))))
			{
				printf("%sSphere has wrong flag\n", ERROR_MESSAGE);
				exit(1);
			}
			ptr = malloc(sizeof(t_sp));
			if (!ptr)
				return (NULL);
			ft_assign_sp(ptr, tmp + 1);
			node = ft_new(ptr);
			node->fl = 0;
			node->chess = 0;
			node->id = j + 1;
			if (n == 5 && fl)
			{
				if (!ft_strcmp(tmp[4], "B"))
					node->fl = 1;
				else if (!ft_strcmp(tmp[4], "C"))
					node->chess = 1;
			}
			else if (n == 6 && fl)
			{
				if ((!ft_strcmp(tmp[4], "B") && !ft_strcmp(tmp[5], "C"))
					|| (!ft_strcmp(tmp[4], "C") && !ft_strcmp(tmp[5], "B")))
				{
					node->fl = 1;
					node->chess = 1;
				}
			}
			ft_add_back(&lt, node);
			j++;
			free(ptr);
		}
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}

t_plane	*ft_obj_pl(char **lst, int fl)
{
	int		i;
	t_plane	*ptr;
	char	**tmp;
	t_plane	*node;
	t_plane	*lt;

	(void)fl;
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

t_cylinder	*ft_obj_cy(char **lst)
{
	int			i;
	t_cylinder	*ptr;
	char		**tmp;
	t_cylinder	*node;
	t_cylinder	*lt;

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

t_cam	*ft_cam(char **lst)
{
	int		i;
	t_cam	*ptr;
	char	**tmp;
	int		c;
	int		n;

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
			n = ft_lst_count(tmp);
			if (n != 4 || c != 1)
			{
				if (c > 1)
				{
					printf("%sOnly one camera is needed\n", ERROR_MESSAGE);
					exit(1);
				}
				else
				{
					printf("%sThe camera has incorrect parameters\n",
						ERROR_MESSAGE);
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
		printf("%sA camera is needed\n", ERROR_MESSAGE);
		exit(1);
	}
	return (ptr);
}

t_light	*ft_light(char **lst)
{
	int		i;
	char	**tmp;
	t_light	*node;
	t_light	*lt;
	int		c;

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

t_alight	*ft_alight(char **lst)
{
	int			i;
	char		**tmp;
	t_alight	*node;
	int			c;

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
