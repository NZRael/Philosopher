/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:10:00 by sboetti           #+#    #+#             */
/*   Updated: 2023/11/20 17:10:22 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	status_print(t_ph ph, char *message)
{
	long int	time;

	pthread_mutex_lock(&ph.p_data->write_mutex);
	time = actual_time_ms() - (ph.p_data->start_time);
	if (is_alive(ph.p_data, 1) && time >= 0 && time <= 2147483647)
	{
		printf("%ld ", time);
		printf("Philo %d %s\n", ph.name, message);
	}
	pthread_mutex_unlock(&ph.p_data->write_mutex);
}

void	routine(t_ph *ph)
{
	if (ph->name == 1 && ph->p_data->nb_philo == 1)
		take_fork_left(ph);
	else
		take_fork_right(ph);
	status_print(*ph, "is eating");
	pthread_mutex_lock(&ph->p_data->eat_mutex);
	ph->time_eaten = actual_time_ms();
	pthread_mutex_unlock(&ph->p_data->eat_mutex);
	ph->count_eat++;
	ft_sleep(ph->p_data->eat_time);
	if (ph->p_data->nb_philo != 1)
	{
		pthread_mutex_unlock((ph->right_fork));
		pthread_mutex_unlock(&(ph->left_fork));
	}
	status_print(*ph, "is sleeping");
	ft_sleep(ph->p_data->sleep_time);
	status_print(*ph, "is thinking");
}

void	take_fork_right(t_ph *ph)
{
	pthread_mutex_lock((ph->right_fork));
	status_print(*ph, "has taken a fork");
	if (ph->p_data->nb_philo == 1)
	{
		pthread_mutex_unlock(ph->right_fork);
		ft_sleep(ph->p_data->life_time * 1.2);
		return ;
	}
	pthread_mutex_lock(&(ph->left_fork));
	status_print(*ph, "has taken a fork");
	return ;
}

void	take_fork_left(t_ph *ph)
{
	pthread_mutex_lock(&(ph->left_fork));
	status_print(*ph, "has taken a fork");
	if (ph->p_data->nb_philo == 1)
	{
		pthread_mutex_unlock(&ph->left_fork);
		ft_sleep(ph->p_data->life_time * 1.2);
		return ;
	}
	pthread_mutex_lock((ph->right_fork));
	status_print(*ph, "has taken a fork");
	return ;
}
