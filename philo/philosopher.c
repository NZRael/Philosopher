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
	t_main	main;

	if (parsing(&main, argv, argc))
		return (1);
	main.philos = malloc(sizeof(t_philo) * main.data.nb_philo);
	if (!main.philos)
		return (ft_error("Malloc returned NULL\n"));
	init_hub(&main);
	end(&main);
	return (0);
}

int	parsing(t_main *main, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (ft_error("Error : Args invalid"));
	if (is_numeric(argv))
		return (1);
	main->data.nb_philo = ft_atoi(argv[1]);
	main->data.life_time = ft_atoi(argv[2]);
	main->data.eat_time = ft_atoi(argv[3]);
	main->data.sleep_time = ft_atoi(argv[4]);
	main->data.death_flag = 0;
	main->data.eat_max = -1;
	main->data.eat_max_flag = 0;
	main->data.philo_done = 0;
	if (argv[5])
		main->data.eat_max = ft_atoi(argv[5]);
	if (main->data.nb_philo <= 0 || main->data.life_time <= 0
		|| main->data.eat_time <= 0
		|| main->data.sleep_time <= 0)
		return (ft_error("Error : Args invalid"));
	return (0);
}

void	end(t_main *main)
{
	int	i;

	i = -1;
	while (1)
	{
		pthread_mutex_lock(&main->data.dead_mutex);
		if (main->data.death_flag > 0)
		{
			pthread_mutex_unlock(&main->data.dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&main->data.dead_mutex);
		ft_sleep(1);
	}
	while (++i < main->data.nb_philo)
		pthread_join(main->philos[i].philo_thread, NULL);
	pthread_join(main->data.death_thread, NULL);
	i = -1;
	while (++i < main->data.nb_philo - 1)
		pthread_mutex_destroy(&main->philos[i].left_fork);
	freeall(main);
}

void	freeall(t_main *main)
{
	free(main->philos);
	pthread_mutex_destroy(&main->data.end_mutex);
	pthread_mutex_destroy(&main->data.write_mutex);
	pthread_mutex_destroy(&main->data.eat_mutex);
	pthread_mutex_destroy(&main->data.dead_mutex);
}
