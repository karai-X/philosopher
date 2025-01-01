/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:49:31 by karai             #+#    #+#             */
/*   Updated: 2025/01/01 11:13:43 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eating(t_philosopher philo)
{
	if (philo.idx % 2 == 1)
	{
		pthread_mutex_lock(philo.right_fork);
		print_custom("has taken a fork", philo);
		pthread_mutex_lock(philo.left_fork);
		print_custom("has taken a fork", philo);
		print_custom("is eating", philo);
		usleep(philo.time_to_eat * 1000);
		pthread_mutex_unlock(philo.left_fork);
		pthread_mutex_unlock(philo.right_fork);
	}
	else
	{
		pthread_mutex_lock(philo.left_fork);
		print_custom("has taken a fork", philo);
		pthread_mutex_lock(philo.right_fork);
		print_custom("has taken a fork", philo);
		print_custom("is eating", philo);
		usleep(philo.time_to_eat * 1000);
		pthread_mutex_unlock(philo.right_fork);
		pthread_mutex_unlock(philo.left_fork);
	}
}

void	sleeping(t_philosopher philo)
{
	print_custom("is sleeping", philo);
	usleep(philo.time_to_sleep * 1000);
}

void	thinking(t_philosopher philo)
{
	print_custom("is thinking", philo);
}

void	*loop_philo(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		eating(*philo);
		sleeping(*philo);
		thinking(*philo);
	}
}

void	print_custom(char *str, t_philosopher philo)
{
	printf("%lu %d %s\n", get_time() - philo.start_time, philo.idx, str);
}
