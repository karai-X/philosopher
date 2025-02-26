/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:16:27 by karai             #+#    #+#             */
/*   Updated: 2025/02/25 23:55:03 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	initialize_overall(char *argv[], t_common *common,
		t_philosopher **philo_array)
{
	int	num_philo;
	int	i;

	num_philo = ft_atoi(argv[1]);
	common->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	common->mutex_die = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	common->last_eat = (size_t *)malloc(sizeof(size_t) * num_philo);
	common->num_philo = num_philo;
	common->time_to_die = (size_t)ft_atoi(argv[2]);
	*philo_array = (t_philosopher *)malloc(sizeof(t_philosopher) * num_philo);
	common->which_eat = (int *)malloc(sizeof(int) * num_philo);
	common->mutex_which_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	common->mutex_last_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	common->philo_array = *philo_array;
	*(common->num_full_philo) = 0;
	*(common->someone_dead) = false;
	*(common->is_eat_finish) = false;
	i = 0;
	while (i < num_philo)
	{
		common->which_eat[i] = RIGHT_EAT;
		i += 1;
	}
}

void	initialize_mutex(char *argv[], t_common *common)
{
	int	num_philo;
	int	i;

	num_philo = ft_atoi(argv[1]);
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&(common->mutex_fork[i]), NULL);
		pthread_mutex_init(&(common->mutex_die[i]), NULL);
		pthread_mutex_init(&(common->mutex_which_eat[i]), NULL);
		pthread_mutex_init(&(common->mutex_last_eat[i]), NULL);
		i += 1;
	}
	pthread_mutex_init(&(common->mutex_write[0]), NULL);
	pthread_mutex_init(&(common->mutex_eat[0]), NULL);
}

void	initialize_main(int argc, char *argv[], t_philosopher **philo_array,
		t_common *common)
{
	initialize_overall(argv, common, philo_array);
	initialize_mutex(argv, common);
	initialize_thread(argc, argv, philo_array, common);
	initialize_start_time(argv, philo_array, common);
}
