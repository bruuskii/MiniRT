/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:15:47 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/24 00:00:59 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include "../structs.h"

int		is_in_sphere(t_vctr *pnt, t_sp *sp);
int		ft_escape_key(int key, void *param);
int		ft_close(t_win *param);
t_win	*ft_window(int height, int width);
void	ft_free_win(t_win *w);
double	ft_magnitude(t_vctr c);

#endif