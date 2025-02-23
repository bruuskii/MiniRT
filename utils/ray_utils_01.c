/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:52:06 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/23 11:16:48 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vctr	*new_vec(double x, double y, double z)
{
	t_vctr	*vctr;

	vctr = malloc(sizeof(t_vctr));
	if (!vctr)
		return (NULL);
	vctr->x = x;
	vctr->y = y;
	vctr->z = z;
	return (vctr);
}

t_vctr	*vec_add(t_vctr v1, t_vctr v2)
{
	t_vctr	*vctr;

	vctr = malloc(sizeof(t_vctr));
	if (!vctr)
		return (NULL);
	vctr->x = v1.x + v2.x;
	vctr->y = v1.y + v2.y;
	vctr->z = v1.z + v2.z;
	return (vctr);
}

t_vctr	*vec_sub(t_vctr v1, t_vctr v2)
{
	t_vctr	*vctr;

	vctr = malloc(sizeof(t_vctr));
	if (!vctr)
		return (NULL);
	vctr->x = v1.x - v2.x;
	vctr->y = v1.y - v2.y;
	vctr->z = v1.z - v2.z;
	return (vctr);
}

t_vctr	*vec_scale(t_vctr v, double d)
{
	t_vctr	*vctr;

	vctr = new_vec(v.x * d, v.y * d, v.z * d);
	if (!vctr)
		return (NULL);
	return (vctr);
}
