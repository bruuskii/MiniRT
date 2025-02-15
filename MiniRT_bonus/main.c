/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:38:04 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/14 02:00:59 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	main(int ac, char **av)
{
	t_win	*data;
	t_scene	*scene;

	if (ft_check_args(ac) || ft_check_extention(av[1]))
		return (1);
	scene = data_input(av[1], 1);
	if (!scene)
		return (1);
	data = malloc(sizeof(t_win));
	if (!data)
		return (1);
	data->ptr = mlx_init();
	if (!data->ptr)
		return (free(data), 1);
	data->win = mlx_new_window(data->ptr, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
	{
		mlx_destroy_display(data->ptr);
		return (1);
	}
	data->img = mlx_new_image(data->ptr, WIDTH, HEIGHT);
	scene->data = data;
	ft_display_scene(scene, data);
	return (0);
}
