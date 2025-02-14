/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:16:49 by izouine           #+#    #+#             */
/*   Updated: 2025/02/06 07:28:11 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	vec3_length(t_vctr vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vctr	vec3_multiply(t_vctr v1, t_vctr v2)
{
	t_vctr	result;

	result.x = (v1.x * v2.x) / 255.0;
	result.y = (v1.y * v2.y) / 255.0;
	result.z = (v1.z * v2.z) / 255.0;
	return (result);
}


