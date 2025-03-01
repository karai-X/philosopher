/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:49:12 by karai             #+#    #+#             */
/*   Updated: 2025/03/01 14:29:25 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

bool	is_finish_in_eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->mutex_which_eat);
	if (*(philo->which_eat) == FINISH)
	{
		pthread_mutex_unlock(philo->mutex_which_eat);
		return (true);
	}
	return (false);
}

void	taken_fork(t_philosopher *philo, pthread_mutex_t *lr_fork)
{
	pthread_mutex_lock(lr_fork);
	pthread_mutex_unlock(philo->mutex_which_eat);
	print_custom("has taken a fork", philo);
	pthread_mutex_lock(philo->mutex_die);
	pthread_mutex_lock(philo->mutex_last_eat);
	*(philo->last_eat) = get_time();
	pthread_mutex_unlock(philo->mutex_last_eat);
}

void	eating_part(t_philosopher *philo)
{
	philo->num_eat += 1;
	if (philo->num_eat == philo->num_times_each_philo_must_eat)
	{
		pthread_mutex_lock(philo->mutex_eat);
		*(philo->num_full_philo) += 1;
		if (*philo->num_full_philo == philo->num_philo)
		{
			pthread_mutex_lock(philo->mutex_write);
			*(philo->is_eat_finish) = true;
			if (*philo->someone_dead == false)
				printf("%lu %d %s\n", get_time() - philo->start_time,
					philo->idx, "is eating");
			pthread_mutex_unlock(philo->mutex_write);
		}
		pthread_mutex_unlock(philo->mutex_eat);
		print_custom("is eating", philo);
	}
	else
		print_custom("is eating", philo);
}

bool	eating_mainpart(t_philosopher *philo, int rl_which_eat,
		pthread_mutex_t *lr_fork)
{
	if (*(philo->which_eat) == rl_which_eat)
	{
		taken_fork(philo, lr_fork);
		if (philo->num_times_each_philo_must_eat != -1)
			eating_part(philo);
		else
			print_custom("is eating", philo);
		pthread_mutex_unlock(philo->mutex_die);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(lr_fork);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(philo->mutex_which_eat);
		return (false);
	}
}

void	eating(t_philosopher *philo)
{
	if (philo->idx % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_custom("has taken a fork", philo);
		while (1)
		{
			if (is_finish_in_eating(philo) || eating_mainpart(philo, RIGHT_EAT,
					philo->left_fork))
				break ;
		}
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_custom("has taken a fork", philo);
		while (1)
		{
			if (is_finish_in_eating(philo) || eating_mainpart(philo, LEFT_EAT,
					philo->right_fork))
				break ;
		}
		pthread_mutex_unlock(philo->left_fork);
	}
}
