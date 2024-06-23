/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcortes <dcortes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:36:44 by damiancorte       #+#    #+#             */
/*   Updated: 2024/06/19 18:08:42 by dcortes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define ALIVE -1
# include <pthread.h>

typedef long int				t_abs;
typedef long int				t_rel;
typedef struct s_philosopher	t_philosopher;

/*
 * Data structure
 */
typedef enum e_action
{
	THINKING,
	EATING,
	SLEEPING,
	FORKS
}	t_action;

typedef struct s_data
{
	t_philosopher	*philosopher;
	pthread_t		*checker;
	int				n;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_stop;
	pthread_mutex_t	lock_stop_print;
	t_abs			timestamp_start;
	t_rel			time_to_die;
	t_rel			time_to_eat;
	t_rel			time_to_sleep;
	int				meal_count;
	int				stop;
	int				stop_printed;
}	t_data;

typedef struct s_philosopher
{
	t_data			*data;
	int				id;
	pthread_t		thread;
	int				fork_left;
	int				fork_right;
	t_action		last_action;
	int				meal_count;
	pthread_mutex_t	lock_last_meal;
	t_abs			timestamp_last_meal;
	t_abs			timestamp_death;
}	t_philosopher;

/*
 * Time
 */
void		msleep(unsigned int ms);
t_abs		now_abs(void);
t_rel		now_rel(t_data *data);
t_rel		elapsed(t_abs end, t_abs start);
t_rel		since_death(t_philosopher *philosopher);
t_rel		since_last_meal(t_philosopher *philosopher);

/*
 * Data
 */
void		init_data(int argc, char **argv, t_data *data);
void		update_last_meal(t_philosopher *philosopher);
void		update_meal_count(t_philosopher *philosopher);

/*
 * Thread
 */
void		*routine(void *args);
void		*routine_single(void *args);
void		thread_create(t_data *data);
void		thread_wait(t_data *data);
void		thread_destroy(t_data *data);

/*
 * Action
 */
void		print_action(t_philosopher *philosopher, t_action action);
void		print_death(t_philosopher *philosopher);
void		*eat(void *args);
void		*think(void *args);
void		*nap(void *args);

/*
 * Fork
 */
void		order_forks(int *fork_first, int *fork_second,
				int fork_left, int fork_right);
int			fork_lock(pthread_mutex_t *fork, int fork_left,
				int fork_right, t_philosopher *philosopher);
void		fork_unlock(pthread_mutex_t *fork, int fork_left, int fork_right);

/*
 * Death
 */
t_abs		is_dead(t_philosopher *philosopher);
void		*check(void *args);
int			get_flag(pthread_mutex_t *lock, int *flag);
void		set_flag(pthread_mutex_t *lock, int *flag, int value);

void		set_stop_flag(t_philosopher *philosopher);
int			must_stop(t_philosopher *philosopher);
int			stop_printed(t_philosopher *philosopher);
void		set_stop_printed(t_philosopher *philosopher);

#endif