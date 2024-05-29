/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadam <kadam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:11:44 by kadam             #+#    #+#             */
/*   Updated: 2024/05/24 16:57:28 by kadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

static size_t	ft_isdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atoi(const char *str)
{
	int	result;
	int	old;
	int	i;

	result = 0;
	old = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (0);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		old = result;
		result = result * 10 + str[i] - '0';
		if (old != (result / 10))
			return (0);
		i++;
	}
	return (result);
}

static int	check_args(char **av, t_data *data, int ac, int i)
{
	while (av[i] != NULL)
	{
		if (ft_atoi(av[i]) <= 0 || ft_isdigit(av[i]) == 0)
			return (0);
		i++;
	}
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = -1;
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || data->nb_philo > 200)
		return (0);
	data->end_simulation = false;
	data->nb_meal_finished = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_stop, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (check_args(av, &data, ac, 1) == 0)
			return (1);
		initialize_all(&data);
	}
	else
		return (1);
	return (0);
}
