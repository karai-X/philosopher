/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:28:13 by karai             #+#    #+#             */
/*   Updated: 2025/02/24 22:08:14 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*waiter(void *arg)
{
	int			i;
	int			j;
	t_common	*common;

	j = 0;
	common = (t_common *)arg;
	while (1)
	{
		i = 0;
		while (i < common->num_philo)
		{
			pthread_mutex_lock(&(common->mutex_last_eat[i]));
			pthread_mutex_lock(&(common->mutex_last_eat[(i + 1)
					% common->num_philo]));
			if (common->last_eat[i] <= common->last_eat[(i + 1)
				% common->num_philo])
			{
				pthread_mutex_unlock(&(common->mutex_last_eat[(i + 1)
						% common->num_philo]));
				pthread_mutex_unlock(&(common->mutex_last_eat[i]));
				pthread_mutex_lock(&(common->mutex_which_eat[i]));
				if (common->which_eat[i] == FINISH)
				{
					pthread_mutex_unlock(&(common->mutex_which_eat[i]));
					return (NULL);
				}
				common->which_eat[i] = RIGHT_EAT;
				pthread_mutex_unlock(&(common->mutex_which_eat[i]));
			}
			else
			{
				pthread_mutex_unlock(&(common->mutex_last_eat[(i + 1)
						% common->num_philo]));
				pthread_mutex_unlock(&(common->mutex_last_eat[i]));
				pthread_mutex_lock(&(common->mutex_which_eat[i]));
				if (common->which_eat[i] == FINISH)
				{
					pthread_mutex_unlock(&(common->mutex_which_eat[i]));
					return (NULL);
				}
				common->which_eat[i] = LEFT_EAT;
				pthread_mutex_unlock(&(common->mutex_which_eat[i]));
			}
			i += 2;
		}
	}
}
