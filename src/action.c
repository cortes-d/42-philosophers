/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:35:01 by damiancorte       #+#    #+#             */
/*   Updated: 2024/06/23 23:23:09 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

/*
 * Message for each action
 */
void	print_action(t_philosopher *philosopher, t_action action)
{
	int		id;
	char	*message;

	if (must_stop(philosopher))
		return ;
	id = philosopher->id + 1;
	if (philosopher->last_action == action)
		return ;
	if (action == THINKING)
		message = "💭\tis thinking";
	if (action == EATING)
		message = "🍽️\tis eating";
	if (action == SLEEPING)
		message = "💤\tis sleeping";
	if (action == FORKS)
		message = "🍴\thas taken forks";
	pthread_mutex_lock(&philosopher->data->lock_print);
	if (!philosopher->data->stop_printed)
	{
		printf("%li\t\tPhilosopher %i\t%s\n",
			now_rel(philosopher->data), id, message);
		philosopher->last_action = action;
	}
	pthread_mutex_unlock(&philosopher->data->lock_print);
}

/*
 * Message when a philosopher dies
 */
void	print_death(t_philosopher *philosopher)
{
	char	*message;
	int		id;

	pthread_mutex_lock(&philosopher->data->lock_print);
	if (philosopher->data->stop_printed)
	{
		pthread_mutex_unlock(&philosopher->data->lock_print);
		return ;
	}
	id = philosopher->id + 1;
	message = "💀\tis dead";
	printf("%li\t\tPhilosopher %i\t%s\n",
		now_rel(philosopher->data), id, message);
	philosopher->data->stop_printed = 1;
	pthread_mutex_unlock(&philosopher->data->lock_print);
	set_stop_printed(philosopher);
}

/*
 * Eat
 */
void	*eat(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	if (must_stop(philosopher))
		return (NULL);
	update_meal_count(philosopher);
	update_last_meal(philosopher);
	print_action(philosopher, EATING);
	msleep(philosopher->data->time_to_eat);
	fork_unlock(philosopher->data->fork,
		philosopher->fork_left, philosopher->fork_right);
	return (NULL);
}

/*
 * Think
 */
void	*think(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	if (must_stop(philosopher))
		return (NULL);
	print_action(philosopher, THINKING);
	return (NULL);
}

/*
 * Sleep
 */
void	*nap(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	if (must_stop(philosopher))
		return (NULL);
	print_action(philosopher, SLEEPING);
	msleep(philosopher->data->time_to_sleep);
	return (NULL);
}
