/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:02:43 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/02 15:49:43 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_plane(t_plane *pl, char **lst, int fl)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		ft_assign_plane_utils(&pl, lst, i, fl);
		i++;
	}
}

void	ft_assign_cy(t_cylinder *cy, char **lst, int n)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		ft_assign_cy_utils(&cy, lst, i, n);
		i++;
	}
}

void	ft_assign_sp(t_sp *sp, char **lst, int fl)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		ft_assign_sp_utils(&sp, lst, i, fl);
		i++;
	}
}

void	ft_assign_camera(t_cam *cam, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (i)
			ft_assign_cam_utils(&cam, tmp, i);
		i++;
	}
}

void	ft_assign_light(t_light *lt, char **lst, int fl)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		ft_assign_light_utils(&lt, lst, i, fl);
		i++;
	}
}
