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

int	init_thread(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->data.nb_philo)
	{
		main->philos[i].p_data = &main->data;
		if (pthread_create(&main->philos[i].philo_thread, NULL,
				&life_cycle, &main->philos[i]) != 0)
			{
				ft_error("- Thread creation error -");
				exit(1);				
			}
		i++;
	}
	pthread_create(&main->data.death_thread, NULL, check_death, (void *) main);
	return (1);
}

void	*life_cycle(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->name % 2 == 0)
		ft_sleep(philo->p_data->eat_time / 2);
	while (is_alive(philo->p_data, 1))
	{
		sleep_eat_think(philo);
		if (philo->p_data->eat_max == philo->count_eat)
		{
			pthread_mutex_lock(&philo->p_data->end_mutex);
			philo->p_data->philo_done++;
			philo->done = 1;
			pthread_mutex_unlock(&philo->p_data->end_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

void	*check_death(void *data)
{
	t_main	*main;
	t_philo	*philo;
	int		i;

	main = (t_main *)data;
	i = 0;
	philo = &main->philos[0];
	while (is_alive(&main->data, 1))
	{
		boucle(main, philo);
		i += 1;
		i %= main->data.nb_philo;
		philo = &main->philos[i];
	}
	return (NULL);
}

void	boucle(t_main *main, t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data->eat_mutex);
	pthread_mutex_lock(&philo->p_data->end_mutex);
	if (is_alive(&main->data, 1) && !philo->done && actual_time_ms()
		- philo->time_eaten >= (philo->p_data->life_time))
	{
		pthread_mutex_unlock(&philo->p_data->eat_mutex);
		pthread_mutex_unlock(&philo->p_data->end_mutex);
		status_print(*philo, " died");
		is_alive(&main->data, 0);
		return ;
	}
	if (main->data.philo_done == main->data.nb_philo)
	{
		pthread_mutex_unlock(&philo->p_data->end_mutex);
		pthread_mutex_unlock(&philo->p_data->eat_mutex);
		printf("- The philos ate %d times -\n", philo->p_data->eat_max);
		is_alive(philo->p_data, 0);
		return ;
	}
	pthread_mutex_unlock(&philo->p_data->eat_mutex);
	pthread_mutex_unlock(&philo->p_data->end_mutex);
}
