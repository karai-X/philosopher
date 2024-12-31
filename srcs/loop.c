/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:49:31 by karai             #+#    #+#             */
/*   Updated: 2024/12/31 16:09:42 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eating(t_philosopher philo)
{
	printf("eat idx , %d,  %lu\n", philo.idx, get_time());
	usleep(philo.time_to_eat * 1000);
}

void	sleeping(t_philosopher philo)
{
	printf("sleep idx , %d,  %lu\n", philo.idx, get_time());
	usleep(philo.time_to_sleep * 1000);
}

void	thinking(t_philosopher philo)
{
	printf("thinking idx , %d,  %lu\n", philo.idx, get_time());
}

void	*loop_philo(void *arg)
{
	t_philosopher	*philo;

	write(1, "b\n", 2);
	philo = (t_philosopher *)arg;
	while (1)
	{
		write(1, "b\n", 2);
		eating(*philo);
		sleeping(*philo);
		thinking(*philo);
	}
}
