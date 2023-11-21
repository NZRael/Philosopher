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

void	init_hub(t_main *main)
{
	pthread_mutex_init(&main->data.write_mutex, NULL);
	pthread_mutex_init(&main->data.eat_mutex, NULL);
	pthread_mutex_init(&main->data.end_mutex, NULL);
	pthread_mutex_init(&main->data.dead_mutex, NULL);
	init_philos(main);
	init_thread(main);
}

void	init_philos(t_main *main)
{
	int	i;

	i = 0;
	main->data.start_time = actual_time_ms();
	while (i < main->data.nb_philo)
	{
		main->philos[i].name = i + 1;
		main->philos[i].count_eat = 0;
		main->philos[i].time_eaten = main->data.start_time;
		main->philos[i].right_fork = NULL;
		main->philos[i].done = 0;
		pthread_mutex_init(&main->philos[i].left_fork, NULL);
		if (main->data.nb_philo == 1)
			break ;
		if (i == main->data.nb_philo - 1)
			main->philos[i].right_fork = &main->philos[0].left_fork;
		else
			main->philos[i].right_fork = &main->philos[i + 1].left_fork;
		i++;
	}
}
