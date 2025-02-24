/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:09:14 by karai             #+#    #+#             */
/*   Updated: 2025/02/24 19:57:35 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	free2dim(char **str_array)
{
	size_t	i;

	if (str_array == NULL)
		return ;
	i = 0;
	while (str_array[i])
	{
		free(str_array[i]);
		i += 1;
	}
	free(str_array);
}

void free_common(t_common *common)
{
	free(common->bool_fork);
	free(common->last_eat);
	free(common->which_eat);
	free(common->mutex_fork);
	free(common->mutex_die);
	free(common->mutex_which_eat);
	free(common->mutex_last_eat);
	free(common->philo_array);
}
