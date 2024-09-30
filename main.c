/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:38:04 by kbassim           #+#    #+#             */
/*   Updated: 2024/09/30 14:38:21 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void  mlx_helpers(void)
{
    t_win *win;

    win = ft_window(HEIGHT, WIDTH);
    if (!win)
        return;
    ft_display(win);
    mlx_key_hook(win->win, ft_escape_key, win);
    mlx_hook(win->win, 17, 0, ft_close, win);
    mlx_loop(win->ptr);
}

int main(int argc, char **argv)
{
    char    **lst;

    if (ft_check_args(argc))
        return (1);
    if (parse_scene_file(argv[1]) || ft_check_extention(argv[1]))
        return (1);
    return (0);
}
