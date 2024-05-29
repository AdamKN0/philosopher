/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:13:59 by kadam             #+#    #+#             */
/*   Updated: 2024/05/24 17:35:05 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

long	current_time(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

void	my_sleep(long time, t_philo *philo)
{
	long	start;

	start = current_time();
	while (current_time() - start < time)
	{
		if (check_end_simulation(philo->data) == true)
			return ;
		usleep(100);
	}
}

void	my_printf(t_philo *philo, char *message, bool end)
{
	bool	end_simulation;

	pthread_mutex_lock(&philo->data->mutex_print);
	pthread_mutex_lock(&philo->data->mutex_stop);
	end_simulation = philo->data->end_simulation;
	pthread_mutex_unlock(&philo->data->mutex_stop);
	if (end_simulation == false || end == true)
		printf("%ld %d %s\n", current_time() - philo->data->start_time,
			philo->philo_id, message);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	my_printf(philo, "has taken a fork", false);
	pthread_mutex_lock(&philo->right_fork->mutex);
	my_printf(philo, "has taken a fork", false);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}
