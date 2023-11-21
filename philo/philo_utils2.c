/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:58:30 by sboetti           #+#    #+#             */
/*   Updated: 2023/11/20 17:24:51 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_numeric(char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10)
			return (ft_error("Error : Number too big"));
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ft_error("Error : No numeric"));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (str[i])
		i++;
	while (++j < i)
		write(2, &str[j], 1);
	write(2, "\n", 1);
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == 32))
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			x = x * 10 + str[i] - '0';
		else
			return (x);
		i++;
	}
	return (x);
}
