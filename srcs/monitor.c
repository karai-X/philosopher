/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:18:55 by karai             #+#    #+#             */
/*   Updated: 2025/01/10 22:22:23 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitor(void *arg)
{
	int			i;
	int			j;
	size_t		time_current;
	t_common	*common;

	j = 0;
	common = (t_common *)arg;
	while (1)
	{
		i = 0;
		while (i < common->num_philo)
		{
			pthread_mutex_lock(common->mutex_write);
			if (*common->is_eat_finish)
			{
				while (j < common->num_philo)
				{
					pthread_detach(common->philo_array[i].thread);
					j += 1;
				}
				pthread_detach(*(common->waiter_thread));
				return (arg);
			}
			pthread_mutex_unlock(common->mutex_write);
			pthread_mutex_lock(&(common->mutex_die[i]));
			time_current = get_time();
			if (time_current - common->last_eat[i] > common->time_to_die)
			{
				pthread_mutex_lock(&(common->mutex_write[0]));
				*(common->someone_dead) = 1;
				pthread_mutex_unlock(&(common->mutex_write[0]));
				while (j < common->num_philo)
				{
					pthread_detach(common->philo_array[i].thread);
					j += 1;
				}
				pthread_detach(*(common->waiter_thread));
				pthread_mutex_lock(common->mutex_write);
				if (*common->is_eat_finish == false)
				{
					printf("%lu %d died\n", get_time() - common->start_time, i
						+ 1);
				}
				pthread_mutex_unlock(common->mutex_write);
				return (arg);
			}
			pthread_mutex_unlock(&(common->mutex_die[i]));
			i += 1;
		}
		usleep(300);
	}
}
