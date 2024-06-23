/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:37:48 by damiancorte       #+#    #+#             */
/*   Updated: 2024/06/19 17:25:29 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "philosophers.h"

/*
 * Check the validity of the passed args
 * Must be digits, 0 or positive
 */
int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || ft_atoi(argv[i]) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if ((argc == 5 || argc == 6) && check_args(argv))
	{
		init_data(argc, argv, &data);
		data.philosopher = malloc(sizeof(t_philosopher) * data.n);
		data.checker = malloc(sizeof(pthread_t) * data.n);
		data.timestamp_start = now_abs();
		thread_create(&data);
		thread_wait(&data);
		thread_destroy(&data);
		free(data.fork);
		free(data.philosopher);
		free(data.checker);
	}
	else
		printf("Error : number of arguments or wrong type");
	return (0);
}
