/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:49:31 by karai             #+#    #+#             */
/*   Updated: 2025/02/27 00:54:52 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

bool	sleeping(t_philosopher *philo)
{
	if (print_custom("is sleeping", philo) == false)
		return (false);
	usleep(philo->time_to_sleep * 1000);
	return (true);
}

bool	thinking(t_philosopher *philo)
{
	if (print_custom("is thinking", philo) == false)
		return (false);
	return (true);
}

void	*loop_philo(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		eating(philo);
		if (sleeping(philo) == false)
		{
			pthread_mutex_lock(philo->mutex_which_eat);
			*(philo->which_eat) = FINISH;
			pthread_mutex_unlock(philo->mutex_which_eat);
			return (NULL);
		}
		if (thinking(philo) == false)
		{
			pthread_mutex_lock(philo->mutex_which_eat);
			*(philo->which_eat) = FINISH;
			pthread_mutex_unlock(philo->mutex_which_eat);
			return (NULL);
		}
	}
	return (NULL);
}

bool	print_custom(char *str, t_philosopher *philo)
{
	pthread_mutex_lock(philo->mutex_write);
	if (!*(philo->someone_dead) && !*(philo->is_eat_finish))
	{
		printf("%lu %d %s\n", get_time() - philo->start_time, philo->idx, str);
	}
	else
	{
		pthread_mutex_unlock(philo->mutex_write);
		return (false);
	}
	pthread_mutex_unlock(philo->mutex_write);
	return (true);
}
