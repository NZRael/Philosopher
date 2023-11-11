/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:52:07 by sboetti           #+#    #+#             */
/*   Updated: 2023/08/03 16:52:07 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc >= 5 && argc <= 6 && is_digit(argv, 1))
	{
		return (1);
	}
	return (0);
}

int	is_digit(char **argv, int j)
{
	int	i;

	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				ft_exit("Args must be positive integers");
			if (ft_strlen(argv[j]) > 10)
				ft_exit("Args must be lower than 10 000 000 000");
			i++;
		}
		j++;
	}
	return (1);
}

void	ft_exit(char *str)
{
	printf("Error :\n");
	printf("%s", str);
	exit(1);
}
