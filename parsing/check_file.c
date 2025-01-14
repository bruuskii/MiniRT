/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:05:59 by kbassim           #+#    #+#             */
/*   Updated: 2024/12/25 00:42:29 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_check_extention(char *s)
{
	char	*chck;

	if (!s)
		return (1);
	chck = ft_strchr(s, '.');
	if (!chck)
		return (printf("%sFile with no extention !\n", ERROR_MESSAGE), 1);
	else if (ft_strcmp(chck, ".rt"))
		return (printf("%sWrong file extention !\n", ERROR_MESSAGE), 1);
	return (0);
}

int	ft_check_args(int ac)
{
	if (ac != 2)
	{
		printf("%sthe program should be ran with :\n", ERROR_MESSAGE);
		printf("    [./miniRT] [filename]\n");
		return (1);
	}
	return (0);
}
