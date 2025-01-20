/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:42:28 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/20 01:58:56 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_check_first_param(char *s)
{
	return (!ft_strcmp(s, "A") || !ft_strcmp(s, "L") || !ft_strcmp(s, "C")
		|| !ft_strcmp(s, "pl") || !ft_strcmp(s, "sp") || !ft_strcmp(s, "cy")
		|| !ft_strcmp(s, "cn"));
}

int	ft_read_lines_from_file(char *filename)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_print_and_exit("Error when opening file", 1), -1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strcmp(line, "") || !ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	ft_count_line(char *filename)
{
	int	i;

	i = ft_read_lines_from_file(filename);
	if (i == -1)
		return (-1);
	if (i > 2147483647)
	{
		ft_print_and_exit("Max Number of lines exceeded!", 1);
		return (-1);
	}
	return (i);
}

void	ft_line_utils(int *c, int fd, char **lst)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strcmp(line, "") || !ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else
		{
			(*c)++;
			lst[i] = line;
		}
		i++;
		line = get_next_line(fd);
	}
	lst[i] = NULL;
}

char	**ft_lines(char *filename)
{
	int		fd;
	char	**lst;
	int		c;

	fd = open(filename, O_RDONLY);
	lst = malloc((ft_count_line(filename) + 1) * sizeof(char *));
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
		return (ft_print_and_exit("Empty file", 1), NULL);
	ft_count_line(filename);
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

void	ft_assign_cone_ptr(char **tmp, t_cone **lt)
{
	t_cone	*ptr;
	t_cone	*node;

	if (ft_lst_count(tmp) != 7)
		ft_print_and_exit("Cone has wrong number of elements", 1);
	ptr = malloc(sizeof(t_cone));
	if (!ptr)
		return ;
	ft_assign_cone(ptr, tmp + 1);
	node = ft_new_cone(ptr);
	ft_add_back_cn(lt, node);
	free(ptr);
}

t_cone	*ft_cone(char **lst, int fl)
{
	int		i;
	char	**tmp;
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
			ft_assign_cone_ptr(tmp, &lt);
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}

void	ft_assign_flag_sphere(int n, char **tmp, t_sp *node, int fl)
{
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
}

void	ft_assign_sphere(char **tmp, t_sp **lt, int n, int fl)
{
	t_sp	*ptr;
	t_sp	*node;

	if (n < 4 || n > 6 || ((n == 5 || n == 6) && !fl))
		ft_print_and_exit("Sphere has incorrect parameters", 1);
	if ((n == 5 && ft_strcmp(tmp[4], "B") && ft_strcmp(tmp[4], "C")) || (n == 6
			&& (ft_strcmp(tmp[4], "B") || ft_strcmp(tmp[5], "C"))
			&& (ft_strcmp(tmp[4], "C") || ft_strcmp(tmp[5], "B"))))
		ft_print_and_exit("Sphere has wrong flag", 1);
	ptr = malloc(sizeof(t_sp));
	if (!ptr)
		return ;
	ft_assign_sp(ptr, tmp + 1);
	node = ft_new(ptr);
	node->fl = 0;
	node->chess = 0;
	ft_assign_flag_sphere(n, tmp, node, fl);
	ft_add_back(lt, node);
	free(ptr);
}

t_sp	*ft_obj(char **lst, int fl)
{
	int		i;
	char	**tmp;
	t_sp	*lt;
	int		n;

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
			n = ft_lst_count(tmp);
			ft_assign_sphere(tmp, &lt, n, fl);
		}
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}

void	ft_assign_ptr_plane(char **tmp, t_plane **lt)
{
	t_plane	*ptr;
	t_plane	*node;

	if (ft_lst_count(tmp) != 4)
		ft_print_and_exit("Plane has wrong number of elements", 1);
	ptr = malloc(sizeof(t_plane));
	if (!ptr)
		return ;
	ft_assign_plane(ptr, tmp + 1);
	node = ft_new_pl(ptr);
	ft_add_back_pl(lt, node);
	free(ptr);
}

t_plane	*ft_obj_pl(char **lst, int fl)
{
	int		i;
	char	**tmp;
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
			ft_assign_ptr_plane(tmp, &lt);
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}

void	ft_assign_cy_ptr(char **tmp, t_cylinder **lt)
{
	t_cylinder	*ptr;
	t_cylinder	*node;

	if (ft_lst_count(tmp) != 6)
		ft_print_and_exit("Cylinder has wrong number of elements", 1);
	ptr = malloc(sizeof(t_cylinder));
	if (!ptr)
		return ;
	ft_assign_cy(ptr, tmp + 1);
	node = ft_new_cy(ptr);
	ft_add_back_cy(lt, node);
	free(ptr);
}

t_cylinder	*ft_obj_cy(char **lst)
{
	int			i;
	char		**tmp;
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
			ft_assign_cy_ptr(tmp, &lt);
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}

void	ft_process_cam(char *entry, t_cam **ptr, int *c)
{
	char	**tmp;
	int		n;

	tmp = ft_fullsplit(entry);
	if (!tmp)
		ft_print_and_exit("Split failed", 1);
	if (!ft_check_first_param(tmp[0]))
		ft_print_and_exit("Undefined object", 1);
	if (!ft_strcmp(tmp[0], "C"))
	{
		(*c)++;
		n = ft_lst_count(tmp);
		if (n != 4 || *c > 1)
		{
			if (*c > 1)
				ft_print_and_exit("Only one camera is needed", 1);
			else
				ft_print_and_exit("The camera has incorrect parameters", 1);
		}
		*ptr = malloc(sizeof(t_cam));
		if (!*ptr)
			ft_print_and_exit("Memory allocation failed", 1);
		ft_assign_camera(*ptr, tmp);
	}
	ft_lstfree(tmp);
}

t_cam	*ft_cam(char **lst)
{
	int		i;
	t_cam	*ptr;
	int		c;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	c = 0;
	ptr = NULL;
	while (lst[i])
	{
		ft_process_cam(lst[i], &ptr, &c);
		i++;
	}
	if (!c)
		ft_print_and_exit("A camera is needed", 1);
	return (ptr);
}

void	ft_process_light(char *entry, t_light **lt, int *c)
{
	char	**tmp;
	t_light	*node;

	tmp = ft_fullsplit(entry);
	if (!tmp)
		ft_print_and_exit("Split failed", 1);
	if (!ft_check_first_param(tmp[0]))
		ft_print_and_exit("Undefined object", 1);
	if (!ft_strcmp(tmp[0], "L"))
	{
		if (ft_lst_count(tmp) != 4)
			ft_print_and_exit("Light has wrong number of elements", 1);
		node = ft_new_lt();
		ft_assign_light(node, tmp + 1);
		ft_add_back_lt(lt, node);
		(*c)++;
	}
	ft_lstfree(tmp);
}

t_light	*ft_light(char **lst)
{
	int		i;
	t_light	*lt;
	int		c;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	c = 0;
	lt = NULL;
	while (lst[i])
	{
		ft_process_light(lst[i], &lt, &c);
		i++;
	}
	if (c == 0)
		ft_print_and_exit("At least one light is needed", 1);
	return (lt);
}

void	ft_alight_ptr(int *c, char **tmp, t_alight **node)
{
	t_alight	*new_node;

	if (!tmp || ft_lst_count(tmp) != 3)
		ft_print_and_exit("Ambient light has wrong number of elements", 1);
	new_node = malloc(sizeof(t_alight));
	if (!new_node)
		ft_print_and_exit("Memory allocation failed", 1);
	ft_assign_alight(new_node, tmp + 1);
	if (*c > 1)
		ft_print_and_exit("Only one ambient light is needed", 1);
	*node = new_node;
	(*c)++;
}

t_alight	*ft_alight(char **lst)
{
	int			i;
	char		**tmp;
	int			c;
	t_alight	*node;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	c = 0;
	while (lst[i])
	{
		tmp = ft_fullsplit(lst[i]);
		if (!tmp)
			ft_print_and_exit("Split failed", 1);
		if (!ft_check_first_param(tmp[0]))
			ft_print_and_exit("Undefined object", 1);
		if (!ft_strcmp(tmp[0], "A"))
			ft_alight_ptr(&c, tmp, &node);
		ft_lstfree(tmp);
		i++;
	}
	if (c == 0)
		ft_print_and_exit("At least one ambient light is needed", 1);
	return (node);
}
