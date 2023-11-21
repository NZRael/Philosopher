/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:47:14 by sboetti           #+#    #+#             */
/*   Updated: 2023/11/20 17:04:41 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init(t_all *all)
{
	pthread_mutex_init(&all->data.write_mutex, NULL);
	pthread_mutex_init(&all->data.eat_mutex, NULL);
	pthread_mutex_init(&all->data.end_mutex, NULL);
	pthread_mutex_init(&all->data.dead_mutex, NULL);
	init_philos(all);
	init_thread(all);
}

void	init_philos(t_all *all)
{
	int	i;

	i = 0;
	all->data.start_time = actual_time_ms();
	while (i < all->data.nb_philo)
	{
		all->philos[i].name = i + 1;
		all->philos[i].count_eat = 0;
		all->philos[i].time_eaten = all->data.start_time;
		all->philos[i].right_fork = NULL;
		all->philos[i].done = 0;
		pthread_mutex_init(&all->philos[i].left_fork, NULL);
		if (all->data.nb_philo == 1)
			break ;
		if (i == all->data.nb_philo - 1)
			all->philos[i].right_fork = &all->philos[0].left_fork;
		else
			all->philos[i].right_fork = &all->philos[i + 1].left_fork;
		i++;
	}
}
