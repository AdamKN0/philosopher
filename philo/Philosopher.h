/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:06:55 by kadam             #+#    #+#             */
/*   Updated: 2024/05/27 11:39:16 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_data
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_must_eat;
	long			start_time;
	bool			end_simulation;
	long			nb_meal_finished;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_stop;
}					t_data;

typedef struct s_philo
{
	int				philo_id;
	t_data			*data;
	pthread_mutex_t	meal_mutex;
	t_fork			my_fork;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			last_meal;
	long			nb_meal_philo_eat;
}					t_philo;

void				is_one_philo(t_philo *philo);
long				current_time(void);
void				my_sleep(long time, t_philo *philo);
void				my_printf(t_philo *philo, char *message, bool end);
void				take_forks(t_philo *philo);
void				drop_forks(t_philo *philo);
bool				check_end_simulation(t_data *data);
void				set_end_simulation(t_data *data);
void				initialize_all(t_data *data);
void				*philo_routine(void *arg);
bool				finished_simulation(t_data *data);

#endif