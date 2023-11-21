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

void	status_print(t_philo philo, char *message)
{
	long int	time;

	pthread_mutex_lock(&philo.p_data->write_mutex);
	time = actual_time_ms() - (philo.p_data->start_time);
	if (is_alive(philo.p_data, 1) && time >= 0 && time <= 2147483647)
	{
		printf ("- %ld ", time);
		printf ("Philo %d %s -\n", philo.name, message);
	}
	pthread_mutex_unlock(&philo.p_data->write_mutex);
}

void	sleep_eat_think(t_philo *philo)
{
	if (philo->name == 1 && philo->p_data->nb_philo == 1)
		take_fork_left(philo);
	else
		take_fork_right(philo);
	status_print(*philo, "is eating");
	pthread_mutex_lock(&philo->p_data->eat_mutex);
	philo->time_eaten = actual_time_ms();
	pthread_mutex_unlock(&philo->p_data->eat_mutex);
	philo->count_eat++;
	ft_sleep(philo->p_data->eat_time);
	if (philo->p_data->nb_philo != 1)
	{
		pthread_mutex_unlock((philo->right_fork));
		pthread_mutex_unlock(&(philo->left_fork));
	}
	status_print(*philo, "is sleeping");
	ft_sleep(philo->p_data->sleep_time);
	status_print(*philo, "is thinking");
}

void	take_fork_right(t_philo *philo)
{
	pthread_mutex_lock((philo->right_fork));
	status_print(*philo, "has taken a fork");
	if (philo->p_data->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		ft_sleep(philo->p_data->life_time * 1.2);
		return ;
	}
	pthread_mutex_lock(&(philo->left_fork));
	status_print(*philo, "has taken a fork");
	return ;
}

void	take_fork_left(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork));
	status_print(*philo, "has taken a fork");
	if (philo->p_data->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->left_fork);
		ft_sleep(philo->p_data->life_time * 1.2);
		return ;
	}
	pthread_mutex_lock((philo->right_fork));
	status_print(*philo, "has taken a fork");
	return ;
}
