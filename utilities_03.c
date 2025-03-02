/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:18 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/23 11:39:32 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_assign_plane_mtrl(t_material *mtrl, t_plane **pl)
{
	(*pl)->mtrl = mtrl;
	(*pl)->mtrl->color = *(*pl)->color;
}

void	ft_assign_cylinder_mtrl(t_material *mtrl, t_cylinder **cy)
{
	(*cy)->mtrl = mtrl;
	(*cy)->mtrl->color = *(*cy)->color;
}

void	ft_assign_cone_mtrl(t_material *mtrl, t_cone **cn)
{
	(*cn)->mtrl = mtrl;
	(*cn)->mtrl->color = *(*cn)->color;
}

void	ft_assign_sphere_mtrl(t_material *mtrl, t_sp **sp)
{
	(*sp)->mtrl = mtrl;
	(*sp)->mtrl->color = *(*sp)->color;
}
