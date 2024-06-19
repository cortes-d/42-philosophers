/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:45:33 by dcortes           #+#    #+#             */
/*   Updated: 2024/06/19 16:45:07 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

/*
 * Sleeps for some milliseconds
 */
void	msleep(unsigned int ms)
{
	t_abs	start;
	t_abs	end;

	start = now_abs();
	end = start + ms;
	while (now_abs() < end)
	{
		usleep(100);
	}
}
