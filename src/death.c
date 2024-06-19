/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:30:20 by damiancorte       #+#    #+#             */
/*   Updated: 2024/06/19 16:21:18 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
 * Death handling
 * Calculates the time elapsed since the last meal.
 * If it is more than the time allowed before a philosopher dies.
 * Returns the time of death or tells the philosopher is alive.
 */
t_abs	is_dead(t_philosopher *philosopher)
{
	t_rel		s_last_meal;
	t_abs		time_of_death;

	pthread_mutex_lock(&philosopher->lock_last_meal);
	s_last_meal = since_last_meal(philosopher);
	pthread_mutex_unlock(&philosopher->lock_last_meal);
	if (s_last_meal > philosopher->data->time_to_die)
	{
		time_of_death = philosopher->timestamp_last_meal
			+ philosopher->data->time_to_die;
		philosopher->timestamp_death = time_of_death;
		return (time_of_death);
	}
	else
		return (ALIVE);
}

/*
 * Monitors the state of a philosopher to determine if he is dead
 */
void	*check(void *args)
{
	t_philosopher	*philosopher;
	t_abs			time_of_death;

	philosopher = (t_philosopher *)args;
	while (!must_stop(philosopher)
		&& philosopher->meal_count != philosopher->data->meal_count)
	{
		time_of_death = is_dead(philosopher);
		if (time_of_death != ALIVE)
		{
			set_stop_flag(philosopher);
			print_death(philosopher);
			break ;
		}
	}
	return (NULL);
}

/*
 * Sets the stop flag to stop the program
 */
void	set_stop_flag(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->lock_stop);
	philosopher->data->stop = 1;
	pthread_mutex_unlock(&philosopher->data->lock_stop);
}

/*
 * Tells if the program must stop (as soon as any philosopher died)
 */
int	must_stop(t_philosopher *philosopher)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&philosopher->data->lock_stop);
	if (philosopher->data->stop)
		stop = 1;
	pthread_mutex_unlock(&philosopher->data->lock_stop);
	return (stop);
}
