/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:59:11 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/02 16:34:13 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_check_txtr(int fl, t_vctr *color_1, t_vctr *color_2)
{
	if (!fl)
		*color_1 = *color_2;
}

t_view	*ft_view(t_vctr light_dir, t_vctr view_dir, t_light *light, t_ray *ray)
{
	t_view	*ptr;

	ptr = malloc(sizeof(t_view));
	if (!ptr)
		return (NULL);
	ptr->light_dir = light_dir;
	ptr->view_dir = view_dir;
	ptr->light = light;
	ptr->ray = ray;
	return (ptr);
}
