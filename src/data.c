/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:36:31 by dcortes           #+#    #+#             */
/*   Updated: 2024/06/19 16:26:38 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "philosophers.h"

/*
 * Initializes the base data
 */
void	init_data(int argc, char **argv, t_data *data)
{
	data->n = ft_atoi(argv[1]);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n);
	data->stop = 0;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meal_count = -1;
	if (argc == 6)
		data->meal_count = ft_atoi(argv[5]);
	pthread_mutex_init(&data->lock_print, NULL);
	pthread_mutex_init(&data->lock_stop, NULL);
}

/*
 * Sets the time of a philosopher's last meal
 */
void	update_last_meal(t_philosopher *philosopher)
{
	int	ret;

	ret = pthread_mutex_lock(&philosopher->lock_last_meal);
	while (ret != 0)
	{
		ret = pthread_mutex_lock(&philosopher->lock_last_meal);
	}
	philosopher->timestamp_last_meal = now_abs();
	pthread_mutex_unlock(&philosopher->lock_last_meal);
}

/*
 * Increments the meal count
 */
void	update_meal_count(t_philosopher *philosopher)
{
	philosopher->meal_count++;
}
