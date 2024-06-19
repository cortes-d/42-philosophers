/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:30:27 by damiancorte       #+#    #+#             */
/*   Updated: 2024/06/19 16:23:59 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philosophers.h"

/*
 * Gives the current time (absolute)
 */
t_abs	now_abs(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000LL + t.tv_usec / 1000);
}

/*
 * Gives the current time (relative to the start time of the program)
 */
t_rel	now_rel(t_data *data)
{
	return (elapsed(now_abs(), data->timestamp_start));
}

/*
 * Interval between `start` and `end`
 */
t_rel	elapsed(t_abs end, t_abs start)
{
	return (end - start);
}

/*
 * Gives the time elapsed since of a philosopher's death
 */
t_rel	since_death(t_philosopher *philosopher)
{
	return (elapsed(now_abs(), philosopher->timestamp_death));
}

/*
 * Gives the time elapsed since of a philosopher's last meal
 */
t_rel	since_last_meal(t_philosopher *philosopher)
{
	return (elapsed(now_abs(), philosopher->timestamp_last_meal));
}
