/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:28:13 by karai             #+#    #+#             */
/*   Updated: 2025/02/25 23:08:10 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

bool	waiter_change_to_rl(t_common *common, int which_eat, int i)
{
	pthread_mutex_unlock(&(common->mutex_last_eat[(i + 1)
			% common->num_philo]));
	pthread_mutex_unlock(&(common->mutex_last_eat[i]));
	pthread_mutex_lock(&(common->mutex_which_eat[i]));
	if (common->which_eat[i] == FINISH)
	{
		pthread_mutex_unlock(&(common->mutex_which_eat[i]));
		return (true);
	}
	common->which_eat[i] = which_eat;
	pthread_mutex_unlock(&(common->mutex_which_eat[i]));
	return (false);
}

void	*waiter(void *arg)
{
	int			i;
	t_common	*common;

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
				if (waiter_change_to_rl(common, RIGHT_EAT, i))
					return (NULL);
			}
			else if (waiter_change_to_rl(common, LEFT_EAT, i))
				return (NULL);
			i += 2;
		}
	}
}
