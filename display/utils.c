/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:05:28 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/06 22:15:49 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"


void convert_3d_to_2d(double x, double y, double z, double d, int *x2, int *y2)
{
    *x2 = (int)((x * d) / (z + d)) + (WIDTH / 2);
    *y2 = (int)((y * d) / (z + d)) + (HEIGHT / 2);
}

int is_in_sphere(t_vctr *pnt, t_sp *sp)
{
    t_vctr  *v;
    double  m;

    v = vct_sub(pnt, sp->cntr);
    m = ft_magnitude(v);
    return (m == (sp->d) / 2);
}



