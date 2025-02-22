/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:49:31 by karai             #+#    #+#             */
/*   Updated: 2025/01/10 21:55:56 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eating(t_philosopher *philo)
{
	if (philo->idx % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		while (1)
		{
			if (*(philo->which_eat) == RIGHT_EAT)
			{
				pthread_mutex_lock(philo->left_fork);
				pthread_mutex_lock(philo->mutex_die);
				if (!*(philo->someone_dead))
				{
					print_custom("has taken a fork", philo);
					print_custom("has taken a fork", philo);
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
								printf("%lu %d %s\n", get_time() - philo->start_time, philo->idx, "is eating");
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
					{
						print_custom("is eating", philo);
					}
					usleep(philo->time_to_eat * 1000);
				}
				pthread_mutex_unlock(philo->mutex_die);
				pthread_mutex_unlock(philo->left_fork);
				break ;
			}
		}
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		while (1)
		{
			if (*(philo->which_eat) == LEFT_EAT)
			{
				pthread_mutex_lock(philo->right_fork);
				pthread_mutex_lock(philo->mutex_die);
				if (!*(philo->someone_dead))
				{
					print_custom("has taken a fork", philo);
					print_custom("has taken a fork", philo);
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
								printf("%lu %d %s\n", get_time() - philo->start_time, philo->idx, "is eating");
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
					{
						print_custom("is eating", philo);
					}
					usleep(philo->time_to_eat * 1000);
				}
				pthread_mutex_unlock(philo->mutex_die);
				pthread_mutex_unlock(philo->right_fork);
				break ;
			}
		}
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	sleeping(t_philosopher *philo)
{
	print_custom("is sleeping", philo);
	usleep(philo->time_to_sleep * 1000);
}

void	thinking(t_philosopher *philo)
{
	print_custom("is thinking", philo);
}

void	*loop_philo(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	print_custom(char *str, t_philosopher *philo)
{
	pthread_mutex_lock(philo->mutex_write);
	if (!*(philo->someone_dead) && !*(philo->is_eat_finish))
	{
		printf("%lu %d %s\n", get_time() - philo->start_time, philo->idx, str);
	}
	pthread_mutex_unlock(philo->mutex_write);
}

// void	print_custom_time(char *str, t_philosopher philo, size_t current_time)
// {
// 	printf("%lu %d %s\n", current_time - philo.start_time, philo.idx, str);
// }
