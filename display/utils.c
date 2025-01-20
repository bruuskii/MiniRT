/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:05:28 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/20 17:29:45 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"


int	is_in_sphere(t_vctr *pnt, t_sp *sp)
{
	t_vctr	*v;
	double	m;

	v = vct_sub(pnt, sp->cntr);
	m = ft_magnitude(v);
	return (m == (sp->d) / 2);
}
