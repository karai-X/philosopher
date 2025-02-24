/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:49:31 by karai             #+#    #+#             */
/*   Updated: 2025/02/24 21:18:07 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	eating(t_philosopher *philo)
{
	if (philo->idx % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		while (1)
		{
			pthread_mutex_lock(philo->mutex_which_eat);
			if (*(philo->which_eat) == RIGHT_EAT)
			{
				pthread_mutex_unlock(philo->mutex_which_eat);
				pthread_mutex_lock(philo->left_fork);
				// {
				print_custom("has taken a fork", philo);
				print_custom("has taken a fork", philo);
				pthread_mutex_lock(philo->mutex_die);
				*(philo->last_eat) = get_time();
				if (philo->num_times_each_philo_must_eat != -1)
				{
					philo->num_eat += 1;
					if (philo->num_eat >= philo->num_times_each_philo_must_eat)
					{
						pthread_mutex_lock(philo->mutex_eat);
						*(philo->num_full_philo) += 1;
						if (*philo->num_full_philo == philo->num_philo)
						{
							pthread_mutex_lock(philo->mutex_write);
							*(philo->is_eat_finish) = true;
							printf("%lu %d %s\n", get_time()
								- philo->start_time, philo->idx, "is eating");
							pthread_mutex_unlock(philo->mutex_write);
						}
						pthread_mutex_unlock(philo->mutex_eat);
						print_custom("is eating", philo);
					}
					else
					{
						print_custom("is eating", philo);
					}
				}
				else
					print_custom("is eating", philo);
				pthread_mutex_unlock(philo->mutex_die);
				usleep(philo->time_to_eat * 1000);
				pthread_mutex_unlock(philo->left_fork);
				break ;
			}
			else
				pthread_mutex_unlock(philo->mutex_which_eat);
		}
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		while (1)
		{
			pthread_mutex_lock(philo->mutex_which_eat);
			if (*(philo->which_eat) == LEFT_EAT)
			{
				pthread_mutex_unlock(philo->mutex_which_eat);
				pthread_mutex_lock(philo->right_fork);
				print_custom("has taken a fork", philo);
				print_custom("has taken a fork", philo);
				pthread_mutex_lock(philo->mutex_die);
				pthread_mutex_lock(philo->mutex_last_eat);
				*(philo->last_eat) = get_time();
				pthread_mutex_unlock(philo->mutex_last_eat);
				if (philo->num_times_each_philo_must_eat != -1)
				{
					philo->num_eat += 1;
					if (philo->num_eat >= philo->num_times_each_philo_must_eat)
					{
						pthread_mutex_lock(philo->mutex_eat);
						*(philo->num_full_philo) += 1;
						if (*philo->num_full_philo == philo->num_philo)
						{
							pthread_mutex_lock(philo->mutex_write);
							*(philo->is_eat_finish) = true;
							printf("%lu %d %s\n", get_time()
								- philo->start_time, philo->idx, "is eating");
							pthread_mutex_unlock(philo->mutex_write);
						}
						pthread_mutex_unlock(philo->mutex_eat);
						print_custom("is eating", philo);
					}
					else
					{
						print_custom("is eating", philo);
					}
				}
				else
					print_custom("is eating", philo);
				pthread_mutex_unlock(philo->mutex_die);
				usleep(philo->time_to_eat * 1000);
				pthread_mutex_unlock(philo->right_fork);
				break ;
			}
			else
				pthread_mutex_unlock(philo->mutex_which_eat);
		}
		pthread_mutex_unlock(philo->left_fork);
	}
}

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
			break ;
		if (thinking(philo) == false)
			break ;
	}
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

// void	print_custom_time(char *str, t_philosopher philo, size_t current_time)
// {
// 	printf("%lu %d %s\n", current_time - philo.start_time, philo.idx, str);
// }
