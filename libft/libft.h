/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:24:16 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/23 22:24:41 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

double	ft_atoi(char *str);
double	ft_atodbl(char *str);
char	**ft_fullsplit(char const *s);
char	**ft_split(char const *s, char c);
int		ft_isdigit(int c);
int		ft_is_void(char c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstfree(char **lst);
#endif