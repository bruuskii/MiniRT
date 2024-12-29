/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:38:04 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/11 21:18:35 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void  mlx_helpers(t_scene *scene)
{
    t_win *win;

    win = ft_window(HEIGHT, WIDTH);
    if (!win)
        return;
    ft_display(win, scene);
    mlx_key_hook(win->win, ft_escape_key, win);
    mlx_hook(win->win, 17, 0, ft_close, win);
    mlx_loop(win->ptr);
}

int main(int argc, char **argv)
{
    t_scene *scene;

    scene = data_input(argv[1]);
    if (!scene)
        return (1);
    if (scene->cam)
        printf("c = %d->",scene->cam->type);
    if (ft_check_args(argc))
        return (1);
    if (ft_check_extention(argv[1]))
        return (1);
    mlx_helpers(scene);
    return (0);
}
