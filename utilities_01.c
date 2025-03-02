/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:43:23 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/30 23:42:05 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_free_all(t_scene **scene)
{
	t_light	*lt;
	t_light	*lt_next;

	if (!scene || !*scene)
		return ;
	if ((*scene)->cam)
	{
		free((*scene)->cam->dir);
		free((*scene)->cam->pos);
		free((*scene)->cam);
	}
	lt = (*scene)->light;
	while (lt)
	{
		lt_next = lt->next;
		free(lt->color);
		free(lt->dir);
		free(lt);
		lt = lt_next;
	}
	free((*scene)->alight->color);
	free((*scene)->alight);
}

void	put_pixel_to_image(char *img_data, int x, int y, int color)
{
	int	offset;

	offset = ((HEIGHT - 1 - y) * WIDTH + x) * 4;
	*(unsigned int *)(img_data + offset) = color;
}
