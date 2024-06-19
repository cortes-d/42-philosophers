/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:35:58 by damiancorte       #+#    #+#             */
/*   Updated: 2024/06/19 16:44:36 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
 * Strategy for picking the forks in a specific order
 * The lower indexed fork is taken first
 * This prevents a deadlock
 */
void	order_forks(int *fork_first, int *fork_second,
		int fork_left, int fork_right)
{
	if (fork_left < fork_right)
	{
		*fork_first = fork_left;
		*fork_second = fork_right;
	}
	else
	{
		*fork_first = fork_right;
		*fork_second = fork_left;
	}
}

/*
 * Locks both forks
 * Returns 1, if successful
 * Return 0, if failed
 */
int	fork_lock(pthread_mutex_t *fork, int fork_left,
	int fork_right, t_philosopher *philosopher)
{
	int	ret;
	int	fork_first;
	int	fork_second;
	int	forks_obtained;

	forks_obtained = 0;
	order_forks(&fork_first, &fork_second, fork_left, fork_right);
	ret = pthread_mutex_lock(&fork[fork_first]);
	if (ret != 0)
		return (forks_obtained);
	ret = pthread_mutex_lock(&fork[fork_second]);
	if (ret != 0 || must_stop(philosopher))
		pthread_mutex_unlock(&fork[fork_first]);
	else
	{
		forks_obtained = 1;
		print_action(philosopher, FORKS);
	}
	return (forks_obtained);
}

/*
 * Unlocks both forks
 */
void	fork_unlock(pthread_mutex_t *fork, int fork_left, int fork_right)
{
	pthread_mutex_unlock(&fork[fork_left]);
	pthread_mutex_unlock(&fork[fork_right]);
}
