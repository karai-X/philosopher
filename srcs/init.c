/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:16:27 by karai             #+#    #+#             */
/*   Updated: 2024/12/31 17:29:44 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	initialize_thread(int argc, char *argv[], t_philosopher **philo_array,
		t_common *common)
{
	int		num_philo;
	int		i;
	size_t start_time;

	start_time = get_time();
	num_philo = ft_atoi(argv[1]);
	*philo_array = (t_philosopher *)malloc(sizeof(t_philosopher) * num_philo);
	i = 0;
	while (i < num_philo)
	{
		(*philo_array)[i].idx = i + 1;
		(*philo_array)[i].num_philo = num_philo;
		(*philo_array)[i].start_time = start_time;
		(*philo_array)[i].time_to_die = ft_atoi(argv[2]);
		(*philo_array)[i].time_to_eat = ft_atoi(argv[3]);
		(*philo_array)[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			(*philo_array)[i].num_times_each_philo_must_eat = ft_atoi(argv[5]);
		else
			(*philo_array)[i].num_times_each_philo_must_eat = -1;
		(*philo_array)[i].right_fork = &(common->mutex_fork[i]);
		(*philo_array)[i].left_fork = &(common->mutex_fork[(i + 1) % num_philo]);
		(*philo_array)[i].right_fork_bool = &(common->bool_fork[i]);
		(*philo_array)[i].left_fork_bool = &(common->bool_fork[(i + 1)
				% num_philo]);
		i += 1;
	}
}

void	initialize_overall(char *argv[], t_common *common)
{
	int	num_philo;
	int	i;

	num_philo = ft_atoi(argv[1]);
	common->bool_fork = (bool *)malloc(sizeof(bool) * num_philo);
	common->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	i = 0;
	while (i < num_philo)
	{
		common->bool_fork[i] = false;
		i += 1;
	}
}

void	initialize_main(int argc, char *argv[], t_philosopher **philo_array,
		t_common *common)
{
	initialize_overall(argv, common);
	initialize_thread(argc, argv, philo_array, common);
}
