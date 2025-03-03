/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:09:14 by karai             #+#    #+#             */
/*   Updated: 2025/02/24 23:01:34 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	free_common(t_common *common)
{
	free(common->last_eat);
	free(common->which_eat);
	free(common->mutex_fork);
	free(common->mutex_die);
	free(common->mutex_which_eat);
	free(common->mutex_last_eat);
	free(common->philo_array);
}

void	destroy(t_common *common)
{
	int	i;

	i = 0;
	while (i < common->num_philo)
	{
		pthread_mutex_destroy(&(common->mutex_fork[i]));
		pthread_mutex_destroy(&(common->mutex_die[i]));
		pthread_mutex_destroy(&(common->mutex_which_eat[i]));
		pthread_mutex_destroy(&(common->mutex_last_eat[i]));
		i += 1;
	}
	pthread_mutex_destroy(common->mutex_write);
	pthread_mutex_destroy(common->mutex_eat);
}

void	join_all(t_philosopher *philo_array, pthread_t monitor_thread,
		pthread_t *waiter_thread, int num_philo)
{
	int	i;

	i = 0;
	pthread_join(monitor_thread, NULL);
	pthread_join(*waiter_thread, NULL);
	while (i < num_philo)
	{
		pthread_join(*(philo_array[i].thread), NULL);
		i += 1;
	}
}
