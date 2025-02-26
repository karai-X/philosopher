/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:18:55 by karai             #+#    #+#             */
/*   Updated: 2025/02/27 00:49:18 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*monitor(void *arg)
{
	int			i;
	t_common	*common;

	common = (t_common *)arg;
	while (1)
	{
		i = 0;
		while (i < common->num_philo)
		{
			if (monitor_died(common, i))
				return (arg);
			i += 1;
		}
		pthread_mutex_lock(common->mutex_write);
		if (*(common->is_eat_finish))
		{
			pthread_mutex_unlock(common->mutex_write);
			return (arg);
		}
		pthread_mutex_unlock(common->mutex_write);
	}
}

bool	monitor_died(t_common *common, int i)
{
	size_t	time_current;

	pthread_mutex_lock(&(common->mutex_die[i]));
	time_current = get_time();
	if (time_current - common->last_eat[i] > common->time_to_die)
	{
		pthread_mutex_lock(&(common->mutex_write[0]));
		if (*common->is_eat_finish == false)
		{
			printf("%lu %d died\n", get_time() - common->start_time, i + 1);
		}
		*(common->someone_dead) = 1;
		pthread_mutex_unlock(&(common->mutex_write[0]));
		pthread_mutex_unlock(&(common->mutex_die[i]));
		return (true);
	}
	pthread_mutex_unlock(&(common->mutex_die[i]));
	return (false);
}
