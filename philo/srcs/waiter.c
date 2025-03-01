/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:28:13 by karai             #+#    #+#             */
/*   Updated: 2025/03/01 13:25:07 by karai            ###   ########.fr       */
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

bool	is_only_philo(t_common *common)
{
	if (common->num_philo == 1)
	{
		common->which_eat[0] = FINISH;
		*(common->someone_dead) = 1;
		return (true);
	}
	return (false);
}

void	*waiter(void *arg)
{
	int			i;
	t_common	*common;

	common = (t_common *)arg;
	if (is_only_philo(common))
		return (NULL);
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
