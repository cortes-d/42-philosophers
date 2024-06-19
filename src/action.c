/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:35:01 by damiancorte       #+#    #+#             */
/*   Updated: 2024/06/19 16:14:56 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

/*
 * Message for each action
 */
void	print_action(t_philosopher *philosopher, t_action action)
{
	int			id;
	char		*message;

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
	printf("%li\t\tPhilosopher %i\t%s\n", now_rel(philosopher->data), id, message);
	pthread_mutex_unlock(&philosopher->data->lock_print);
	philosopher->last_action = action;
}

/*
 * Message when a philosopher dies
 */
void	print_death(t_philosopher *philosopher)
{
	char	*message;
	int		id;

	id = philosopher->id + 1;
	message = "💀\tis dead";
	pthread_mutex_lock(&philosopher->data->lock_print);
	printf("%li\t\tPhilosopher %i\t%s (%li ms ago)\n",
		now_rel(philosopher->data), id, message, since_death(philosopher));
	pthread_mutex_unlock(&philosopher->data->lock_print);
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
