/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:13:46 by dcortes           #+#    #+#             */
/*   Updated: 2024/06/20 14:03:20 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_flag(pthread_mutex_t *lock, int *flag)
{
	int	value;

	pthread_mutex_lock(lock);
	value = *flag;
	pthread_mutex_unlock(lock);
	return (value);
}

void	set_flag(pthread_mutex_t *lock, int *flag, int value)
{
	pthread_mutex_lock(lock);
	*flag = value;
	pthread_mutex_unlock(lock);
}
