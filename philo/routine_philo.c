/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:52:56 by kadam             #+#    #+#             */
/*   Updated: 2024/05/24 17:01:16 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

static void	increment_counter(t_data *data)
{
	pthread_mutex_lock(&data->mutex_stop);
	data->nb_meal_finished++;
	pthread_mutex_unlock(&data->mutex_stop);
}

static void	check_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = current_time();
	philo->nb_meal_philo_eat++;
	if (philo->data->nb_must_eat != -1
		&& philo->nb_meal_philo_eat == philo->data->nb_must_eat)
		increment_counter(philo->data);
	pthread_mutex_unlock(&philo->meal_mutex);
}

static void	is_sleeping(t_philo *philo)
{
	my_printf(philo, "is sleeping", false);
	my_sleep(philo->data->time_to_sleep, philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
		return (is_one_philo(philo), NULL);
	if (philo->philo_id % 2 == 0)
		is_sleeping(philo);
	while (check_end_simulation(philo->data) == false)
	{
		my_printf(philo, "is thinking", false);
		take_forks(philo);
		check_meal(philo);
		my_printf(philo, "is eating", false);
		my_sleep(philo->data->time_to_eat, philo);
		drop_forks(philo);
		if (check_end_simulation(philo->data) == true)
			return (NULL);
		my_printf(philo, "is sleeping", false);
		my_sleep(philo->data->time_to_sleep, philo);
	}
	return (NULL);
}
