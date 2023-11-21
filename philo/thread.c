/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:10:53 by sboetti           #+#    #+#             */
/*   Updated: 2023/11/21 02:10:47 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_thread(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.nb_philo)
	{
		all->philos[i].p_data = &all->data;
		if (pthread_create(&all->philos[i].philo_thread, NULL,
				&life_cycle, &all->philos[i]) != 0)
		{
			ft_error("Error : Thread creation");
			exit(1);
		}
		i++;
	}
	pthread_create(&all->data.death_thread, NULL, check_death, (void *) all);
	return (1);
}

void	*life_cycle(void *data)
{
	t_ph		*ph;

	ph = (t_ph *)data;
	if (ph->id % 2 == 0)
		ft_sleep(ph->p_data->eat_time / 2);
	while (is_alive(ph->p_data, 1))
	{
		routine(ph);
		if (ph->p_data->eat_max == ph->count_eat)
		{
			pthread_mutex_lock(&ph->p_data->end_mutex);
			ph->p_data->philo_done++;
			ph->done = 1;
			pthread_mutex_unlock(&ph->p_data->end_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

void	*check_death(void *data)
{
	t_all	*all;
	t_ph	*ph;
	int		i;

	all = (t_all *)data;
	i = 0;
	ph = &all->philos[0];
	while (is_alive(&all->data, 1))
	{
		boucle(all, ph);
		i += 1;
		i %= all->data.nb_philo;
		ph = &all->philos[i];
	}
	return (NULL);
}

void	boucle(t_all *all, t_ph *ph)
{
	pthread_mutex_lock(&ph->p_data->eat_mutex);
	pthread_mutex_lock(&ph->p_data->end_mutex);
	if (is_alive(&all->data, 1) && !ph->done && actual_time_ms()
		- ph->time_eaten >= (ph->p_data->life_time))
	{
		pthread_mutex_unlock(&ph->p_data->eat_mutex);
		pthread_mutex_unlock(&ph->p_data->end_mutex);
		status_print(*ph, " died");
		is_alive(&all->data, 0);
		return ;
	}
	if (all->data.philo_done == all->data.nb_philo)
	{
		pthread_mutex_unlock(&ph->p_data->end_mutex);
		pthread_mutex_unlock(&ph->p_data->eat_mutex);
		printf("Philo(s) ate %d times\n", ph->p_data->eat_max);
		is_alive(ph->p_data, 0);
		return ;
	}
	pthread_mutex_unlock(&ph->p_data->eat_mutex);
	pthread_mutex_unlock(&ph->p_data->end_mutex);
}
