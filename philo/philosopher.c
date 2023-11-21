/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:55:25 by sboetti           #+#    #+#             */
/*   Updated: 2023/08/02 15:55:25 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_all	all;

	if (parsing(&all, argv, argc))
		return (1);
	all.philos = malloc(sizeof(t_ph) * all.data.nb_philo);
	if (!all.philos)
		return (ft_error("Malloc returned NULL\n"));
	init(&all);
	end(&all);
	return (0);
}

int	parsing(t_all *all, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (ft_error("Error : Args invalid"));
	if (is_numeric(argv))
		return (1);
	all->data.nb_philo = ft_atoi(argv[1]);
	all->data.life_time = ft_atoi(argv[2]);
	all->data.eat_time = ft_atoi(argv[3]);
	all->data.sleep_time = ft_atoi(argv[4]);
	all->data.death_flag = 0;
	all->data.eat_max = -1;
	all->data.eat_max_flag = 0;
	all->data.philo_done = 0;
	if (argv[5])
		all->data.eat_max = ft_atoi(argv[5]);
	if (all->data.nb_philo <= 0 || all->data.life_time <= 0
		|| all->data.eat_time <= 0
		|| all->data.sleep_time <= 0)
		return (ft_error("Error : Args invalid"));
	return (0);
}

void	end(t_all *all)
{
	int	i;

	i = -1;
	while (1)
	{
		pthread_mutex_lock(&all->data.dead_mutex);
		if (all->data.death_flag > 0)
		{
			pthread_mutex_unlock(&all->data.dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&all->data.dead_mutex);
		ft_sleep(1);
	}
	while (++i < all->data.nb_philo)
		pthread_join(all->philos[i].philo_thread, NULL);
	pthread_join(all->data.death_thread, NULL);
	i = -1;
	while (++i < all->data.nb_philo - 1)
		pthread_mutex_destroy(&all->philos[i].left_fork);
	freeall(all);
}

void	freeall(t_all *all)
{
	free(all->philos);
	pthread_mutex_destroy(&all->data.end_mutex);
	pthread_mutex_destroy(&all->data.write_mutex);
	pthread_mutex_destroy(&all->data.eat_mutex);
	pthread_mutex_destroy(&all->data.dead_mutex);
}
