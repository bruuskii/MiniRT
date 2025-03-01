/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:15:47 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/01 18:31:54 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include "../structs.h"

int		ft_escape_key(int key, void *param);
int		ft_close(t_win *param);
void	ft_free_win(t_win *w);
double	ft_magnitude(t_vctr c);

#endif