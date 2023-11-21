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

typedef struct s_ph
{
	int					id;
	pthread_t			philo_thread;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	long int			time_eaten;
	int					count_eat;
	int					done;
	t_data				*p_data;
}						t_ph;

typedef struct s_all
{
	t_data	data;
	t_ph	*philos;
}			t_all;

void 		init(t_all *all);
int			parsing(t_all *all, char **argv, int argc);
void		end(t_all *all);
void		freeall(t_all *all);
void		init_philos(t_all *all);
int			init_thread(t_all *all);
void		status_print(t_ph ph, char *message);
void		*life_cycle(void *data);
void		routine(t_ph *ph);
void		take_fork_right(t_ph *ph);
void		take_fork_left(t_ph *ph);
void		boucle(t_all *all, t_ph *ph);
long int	actual_time_ms(void);
int			is_alive(t_data *data, int i);
void		ft_sleep(long int delay);
void		*check_death(void *data);
int			is_numeric(char **argv);
int			ft_strlen(char *str);
int			ft_atoi(char *str);
int			ft_error(char *str);

#endif
