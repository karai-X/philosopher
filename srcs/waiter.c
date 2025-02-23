/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:28:13 by karai             #+#    #+#             */
/*   Updated: 2025/02/23 14:50:58 by karai            ###   ########.fr       */
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
			if (common->last_eat[i] <= common->last_eat[(i + 1)
				% common->num_philo])
			{
				common->which_eat[i] = RIGHT_EAT;
			}
			else
			{
				common->which_eat[i] = LEFT_EAT;
			}
			i += 2;
		}
		// if (*(common->someone_dead) || *(common->is_eat_finish))
		// 	return (arg);
	}
}
