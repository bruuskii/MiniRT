/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:06:46 by kbassim           #+#    #+#             */
/*   Updated: 2024/09/30 16:06:48 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_free_win(t_win *w)
{
	if (w->img)
		mlx_destroy_image(w->ptr, w->img);
	if (w->win)
		mlx_destroy_window(w->ptr, w->win);
	if (w->ptr)
	{
		mlx_destroy_display(w->ptr);
		free(w->ptr);
	}
	free(w);
	exit(0);
}
