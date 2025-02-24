/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:21:21 by karai             #+#    #+#             */
/*   Updated: 2025/02/24 22:39:58 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int argc, char *argv[])
{
	t_philosopher	*philo_array;
	t_common		common[1];
	int				i;
	pthread_t		monitor_thread;

	// pthread_t		waiter_thread;
	if (error_main(argc, argv))
		return (1);
	initialize_main(argc, argv, &philo_array, common);
	pthread_create(common->waiter_thread, NULL, &waiter, (void *)common);
	pthread_create(&monitor_thread, NULL, &monitor, (void *)common);
	usleep(1000);
	i = 0;
	while (i < philo_array[0].num_philo)
	{
		pthread_create((&philo_array[i])->thread, NULL, &loop_philo,
			(void *)(&(philo_array[i])));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < philo_array[0].num_philo)
	{
		pthread_create((&philo_array[i])->thread, NULL, &loop_philo,
			(void *)(&(philo_array[i])));
		i += 2;
	}
	join_all(philo_array, monitor_thread, common->waiter_thread,
		philo_array[0].num_philo);
	destroy(common);
	free_common(common);
}
