/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:17:23 by kadam             #+#    #+#             */
/*   Updated: 2024/05/24 17:35:08 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

void	is_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	my_printf(philo, "has taken a fork", false);
	my_sleep(philo->data->time_to_die, philo);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	my_printf(philo, "died", true);
}

bool	check_end_simulation(t_data *data)
{
	bool	stop_program;

	pthread_mutex_lock(&data->mutex_stop);
	stop_program = data->end_simulation;
	pthread_mutex_unlock(&data->mutex_stop);
	return (stop_program);
}

void	set_end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->mutex_stop);
	data->end_simulation = true;
	pthread_mutex_unlock(&data->mutex_stop);
}

bool	finished_simulation(t_data *data)
{
	bool	philos_finished;

	pthread_mutex_lock(&data->mutex_stop);
	if (data->nb_meal_finished == data->nb_philo)
		philos_finished = true;
	else
		philos_finished = false;
	pthread_mutex_unlock(&data->mutex_stop);
	return (philos_finished);
}
