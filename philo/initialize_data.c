/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:23:18 by kadam             #+#    #+#             */
/*   Updated: 2024/05/29 20:07:04 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

static void	initialize_philo_fork(t_data *data, t_philo *philo, int i)
{
	t_fork	*a_fork;
	t_fork	*b_fork;

	while (i < data->nb_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].nb_meal_philo_eat = 0;
		philo[i].data = data;
		philo[i].last_meal = current_time();
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		pthread_mutex_init(&philo[i].my_fork.mutex, NULL);
		a_fork = &philo[i].my_fork;
		if (i == data->nb_philo - 1)
			b_fork = &philo[0].my_fork;
		else
			b_fork = &philo[i + 1].my_fork;
		if (i % 2 == 0)
		{
			a_fork = b_fork;
			b_fork = &philo[i].my_fork;
		}
		philo[i].left_fork = a_fork;
		philo[i].right_fork = b_fork;
		i++;
	}
}

static void	help(t_data *data, t_philo *philo, pthread_t *thread_philo)
{
	int	i;

	i = 0;
	data->start_time = current_time();
	while (i < data->nb_philo)
	{
		pthread_create(&thread_philo[i], NULL, &philo_routine, &philo[i]);
		i++;
	}
}

static void	create_thread(t_data *data, t_philo *philo, pthread_t *thread_philo,
		int i)
{
	help(data, philo, thread_philo);
	if (philo->data->nb_philo == 1)
		return ;
	while (1)
	{
		i = 0;
		if (finished_simulation(data) == true)
		{
			set_end_simulation(data);
			return ;
		}
		while (i < philo->data->nb_philo)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			if (current_time() - philo[i].last_meal > philo->data->time_to_die)
			{
				set_end_simulation(data);
				my_printf(philo, "died", true);
				pthread_mutex_unlock(&philo[i].meal_mutex);
				return ;
			}
			pthread_mutex_unlock(&philo[i].meal_mutex);
			i++;
		}
	}
}

static void	clean_all(t_data *data, t_philo *philo, pthread_t *thread_philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_join(thread_philo[i++], NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].meal_mutex);
		pthread_mutex_destroy(&philo[i].my_fork.mutex);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_stop);
	free(philo);
	free(thread_philo);
}

void	initialize_all(t_data *data)
{
	t_philo		*philo;
	pthread_t	*thread_philo;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return ;
	thread_philo = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread_philo)
	{
		free(philo);
		return ;
	}
	initialize_philo_fork(data, philo, 0);
	create_thread(data, philo, thread_philo, 0);
	clean_all(data, philo, thread_philo);
}
