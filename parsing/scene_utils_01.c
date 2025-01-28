/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:20:57 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/27 23:21:14 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_swap_circle(t_sp *a, t_sp *b)
{
	t_sp	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

void	swap_planes(t_plane *a, t_plane *b)
{
	t_plane	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

void	swap_cylinders(t_cylinder *a, t_cylinder *b)
{
	t_cylinder	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

void	swap_cones(t_cone *a, t_cone *b)
{
	t_cone	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}
