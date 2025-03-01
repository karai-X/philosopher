/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:16:27 by karai             #+#    #+#             */
/*   Updated: 2025/02/27 23:07:05 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

bool	initialize_malloc(t_common *common, int num_philo,
		t_philosopher **philo_array)
{
	common->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	if (common->mutex_fork == NULL)
		return (true);
	common->mutex_die = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	if (common->mutex_die == NULL)
		return (true);
	common->last_eat = (size_t *)malloc(sizeof(size_t) * num_philo);
	if (common->last_eat == NULL)
		return (true);
	*philo_array = (t_philosopher *)malloc(sizeof(t_philosopher) * num_philo);
	common->philo_array = *philo_array;
	if (*philo_array == NULL)
		return (true);
	common->which_eat = (int *)malloc(sizeof(int) * num_philo);
	if (common->which_eat == NULL)
		return (true);
	common->mutex_which_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	common->mutex_last_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	if (common->mutex_last_eat == NULL || common->mutex_which_eat == NULL)
		return (true);
	return (false);
}

bool	initialize_overall(char *argv[], t_common *common,
		t_philosopher **philo_array)
{
	int	num_philo;
	int	i;

	common->mutex_fork = NULL;
	common->mutex_die = NULL;
	common->last_eat = NULL;
	*philo_array = NULL;
	common->which_eat = NULL;
	common->mutex_which_eat = NULL;
	common->mutex_last_eat = NULL;
	num_philo = ft_atoi(argv[1]);
	common->time_to_die = (size_t)ft_atoi(argv[2]);
	common->num_philo = num_philo;
	*(common->num_full_philo) = 0;
	*(common->someone_dead) = false;
	*(common->is_eat_finish) = false;
	if (initialize_malloc(common, num_philo, philo_array))
		return (free_common(common), true);
	i = 0;
	while (i < num_philo)
		common->which_eat[i++] = RIGHT_EAT;
	return (false);
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

bool	initialize_main(int argc, char *argv[], t_philosopher **philo_array,
		t_common *common)
{
	if (initialize_overall(argv, common, philo_array))
		return (true);
	initialize_mutex(argv, common);
	initialize_thread(argc, argv, philo_array, common);
	initialize_start_time(argv, philo_array, common);
	return (false);
}
