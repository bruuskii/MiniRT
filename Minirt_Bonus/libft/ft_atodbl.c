/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:19:07 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/11 07:01:10 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	ft_atoi(char *str)
{
	int		i;
	double	sum;

	sum = 0.0;
	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && str[i] != '.')
		sum = sum * 10 + str[i++] - '0';
	return (sum);
}

double	ft_atodbl(char *str)
{
	double	sum0;
	double	sum1;
	double	decimal;
	int		i;

	sum0 = ft_atoi(str);
	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (!str[i])
		return (sum0);
	i++;
	sum1 = 0.0;
	decimal = 0.1;
	while (str[i])
	{
		sum1 += (str[i++] - '0') * decimal;
		decimal *= 0.1;
	}
	sum0 += sum1;
	if (str[0] == '-')
		sum0 *= -1;
	return (sum0);
}
