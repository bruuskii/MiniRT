/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:27:30 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/23 11:25:21 by kbassim          ###   ########.fr       */
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
	if (n == 5 && fl)
	{
		if (!ft_strcmp(tmp[4], "C"))
			ft_print_and_exit("Insufficient Parameters", 1);
	}
	else if (n == 6 && fl)
	{
		node->texture = 1;
		node->txtr_ref = ft_strdup(tmp[5]);
		if (ft_check_txtr_extention(node->txtr_ref))
			return ;
	}
}

int	check_input_bonus(int n, char **tmp)
{
	if (n == 5)
	{
		if (ft_strcmp(tmp[4], "B") && ft_strcmp(tmp[4], "C")
			&& ft_strcmp(tmp[4], "T"))
			return (1);
	}
	if (n == 6)
	{
		if ((ft_strcmp(tmp[4], "C") || (!ft_strcmp(tmp[4], "C") && !tmp[5])))
			return (1);
	}
	return (0);
}

void	ft_assign_sphere(char **tmp, t_sp **lt, int n, int fl)
{
	t_sp	*ptr;
	t_sp	*node;

	if (n < 4 || n > 6 || ((n == 5 || n == 6) && !fl))
		ft_print_and_exit("Sphere has incorrect parameters", 1);
	if (check_input_bonus(n, tmp))
		ft_print_and_exit("Sphere has wrong flag", 1);
	ptr = malloc(sizeof(t_sp));
	if (!ptr)
		return ;
	ft_assign_sp(ptr, tmp + 1);
	node = ft_new(ptr);
	node->fl = 0;
	node->texture = 0;
	ft_assign_flag_sphere(n, tmp, node, fl);
	ft_add_back(lt, node);
	free(ptr);
}
