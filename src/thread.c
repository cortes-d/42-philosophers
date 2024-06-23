/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:03:35 by dcortes           #+#    #+#             */
/*   Updated: 2024/06/19 18:08:33 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
 * Main routine for each philosopher thread. 
 * Handles the cycle of trying to pick up forks,
 * eating, sleeping, and thinking,
 * as long as the simulation is running and the philosopher
 * has not finished their meals.
 */
void	*routine(void *args)
{
	t_philosopher	*philosopher;
	int				forks_obtained;

	philosopher = (t_philosopher *)args;
	update_last_meal(philosopher);
	if (philosopher->data->n == 1)
		return (routine_single(args));
	while (!must_stop(philosopher)
		&& philosopher->meal_count != philosopher->data->meal_count)
	{
		forks_obtained = fork_lock(philosopher->data->fork,
				philosopher->fork_left, philosopher->fork_right, philosopher);
		while (!must_stop(philosopher) && !forks_obtained)
		{
			think(args);
			forks_obtained = fork_lock(philosopher->data->fork,
					philosopher->fork_left,
					philosopher->fork_right,
					philosopher);
		}
		eat(args);
		nap(args);
		think(args);
	}
	return (NULL);
}

/*
 * Special routine for a single philosopher scenario.
 * It continuously thinks until he dies,
 * as it cannot eat without a second fork.
 */
void	*routine_single(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	while (!must_stop(philosopher))
		think(args);
	return (NULL);
}

/*
 * Initializes and starts threads for each philosopher
 * and their corresponding checker.
 * Sets up each philosopher's initial state and forks.
 */
void	thread_create(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_mutex_init(&data->philosopher[i].lock_last_meal, NULL);
		data->philosopher[i].data = data;
		data->philosopher[i].id = i;
		data->philosopher[i].last_action = -1;
		data->philosopher[i].meal_count = 0;
		data->philosopher[i].fork_left = i;
		data->philosopher[i].fork_right = (i - 1 + data->n) % data->n;
		pthread_create(&data->philosopher[i].thread, NULL, &routine,
			(void *)&data->philosopher[i]);
		pthread_create(&data->checker[i], NULL, &check,
			(void *)&data->philosopher[i]);
		i++;
	}
}

/*
 * Waits for all philosopher and checker threads to finish before continuing.
 * Ensures that the simulation does not terminate prematurely.
 */
void	thread_wait(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		pthread_join(data->philosopher[i].thread, NULL);
		pthread_join(data->checker[i], NULL);
		i++;
	}
}

/*
 * Cleans up and destroys all mutexes
 * created for the simulation.
 */
void	thread_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philosopher[i].lock_last_meal);
		i++;
	}
	pthread_mutex_destroy(&data->lock_print);
	pthread_mutex_destroy(&data->lock_stop);
	pthread_mutex_destroy(&data->lock_stop_print);
}
