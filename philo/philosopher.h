/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboetti <sboetti@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:33:49 by sboetti           #+#    #+#             */
/*   Updated: 2023/08/02 15:33:49 by sboetti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_philo;
	int				eat_max;
	int				philo_done;
	int				eat_max_flag;
	int				death_flag;
	pthread_t		death_thread;

	int				life_time;
	int				eat_time;
	int				sleep_time;

	pthread_mutex_t	write_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	end_mutex;

	long int		start_time;
}					t_data;

typedef struct s_philo
{
	int					name;
	pthread_t			philo_thread;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	long int			time_eaten;
	int					count_eat;
	int					done;
	t_data				*p_data;
}						t_philo;

typedef struct s_main
{
	t_data	data;
	t_philo	*philos;
}			t_main;

void		init_hub(t_main *main);
int			parsing(t_main *main, char **argv, int argc);
void		end(t_main *main);
void		freeall(t_main *main);
void		init_philos(t_main *main);
int			init_thread(t_main *main);
void		status_print(t_philo philo, char *message);
void		*life_cycle(void *data);
void		sleep_eat_think(t_philo *philo);
void		take_fork_right(t_philo *philo);
void		take_fork_left(t_philo *philo);
void		boucle(t_main *main, t_philo *philo);
long int	actual_time_ms(void);
int			is_alive(t_data *data, int i);
void		ft_sleep(long int delay);
void		*check_death(void *data);
int			is_numeric(char **argv);
int         ft_strlen(char *str);
int			ft_atoi(char *str);
int			ft_error(char *str);

#endif
