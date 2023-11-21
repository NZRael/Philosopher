/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:52:07 by sboetti           #+#    #+#             */
/*   Updated: 2023/11/21 00:44:52 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_sleep(long int delay)
{
	long int	beginning;

	beginning = actual_time_ms();
	while (actual_time_ms() - beginning < delay)
		usleep(delay / 5);
}

long int	actual_time_ms(void)
{
	struct timeval	gtod_struct;
	long int		time_ms;

	if (gettimeofday(&gtod_struct, NULL) == -1)
	{
		ft_error("Error : gettimeofday return value -1");
		exit(1);
	}
	time_ms = (gtod_struct.tv_sec * 1000) + (gtod_struct.tv_usec / 1000);
	return (time_ms);
}

int	is_alive(t_data *data, int i)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (i == 0)
		data->death_flag = 1;
	if (data->death_flag == 1)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (1);
}
