/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:27:30 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/05 17:11:56 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_lst_count(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		i++;
	return (i);
}

void	ft_assign_flag_sphere(int n, char **tmp, t_sp *node, int fl)
{
	if (n != 4 && !fl)
		ft_print_and_exit("Incorrect Parameters", 1);
	else if ((n > 5 || n < 4) && fl)
		ft_print_and_exit("Incorrect Parameters", 1);
	else if (fl && n == 5)
	{
		if (!tmp[4])
			ft_print_and_exit("Missing texture path", 1);
		node->texture = 1;
		node->txtr_ref = ft_strdup(tmp[4]);
		if (ft_check_txtr_extention(node->txtr_ref))
			return ;
	}
}

int	check_input_bonus(int n, char **tmp)
{
	if (n == 5 || n == 4)
	{
		if ((!ft_strcmp(tmp[3], "T") && tmp[4]) || n == 4)
			return (0);
	}
	return (1);
}

void	ft_assign_sphere(char **tmp, t_sp **lt, int n, int fl)
{
	t_sp	*ptr;
	t_sp	*node;

	if (n < 4 || n > 5)
		ft_print_and_exit("Sphere has incorrect parameters", 1);
	if (fl)
		if (check_input_bonus(n, tmp))
			ft_print_and_exit("Sphere has wrong flag", 1);
	ptr = malloc(sizeof(t_sp));
	if (!ptr)
		return ;
	ft_assign_sp(ptr, tmp + 1, n);
	node = ft_new(ptr);
	node->fl = 0;
	node->texture = 0;
	ft_assign_flag_sphere(n, tmp, node, fl);
	ft_add_back(lt, node);
	free(ptr);
}
