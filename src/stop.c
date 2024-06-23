/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:23:53 by dcortes           #+#    #+#             */
/*   Updated: 2024/06/20 10:30:25 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_stop_flag(t_philosopher *philosopher)
{
	set_flag(&philosopher->data->lock_stop, &philosopher->data->stop, 1);
}

int	must_stop(t_philosopher *philosopher)
{
	return (get_flag(&philosopher->data->lock_stop, &philosopher->data->stop));
}

int	stop_printed(t_philosopher *philosopher)
{
	return (get_flag(&philosopher->data->lock_stop_print,
			&philosopher->data->stop_printed));
}

void	set_stop_printed(t_philosopher *philosopher)
{
	set_flag(&philosopher->data->lock_stop_print,
		&philosopher->data->stop_printed, 1);
}
