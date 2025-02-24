/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:16:27 by karai             #+#    #+#             */
/*   Updated: 2025/02/24 19:45:52 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	initialize_thread(int argc, char *argv[], t_philosopher **philo_array,
		t_common *common)
{
	int		num_philo;
	int		i;
	size_t	start_time;

	start_time = get_time();
	common->start_time = start_time;
	num_philo = ft_atoi(argv[1]);
	i = 0;
	while (i < num_philo)
	{
		(*philo_array)[i].idx = i + 1;
		(*philo_array)[i].num_philo = num_philo;
		(*philo_array)[i].start_time = start_time;
		common->last_eat[i] = start_time;
		(*philo_array)[i].last_eat = &(common->last_eat[i]);
		(*philo_array)[i].time_to_die = ft_atoi(argv[2]);
		(*philo_array)[i].time_to_eat = ft_atoi(argv[3]);
		(*philo_array)[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			(*philo_array)[i].num_times_each_philo_must_eat = ft_atoi(argv[5]);
		else
			(*philo_array)[i].num_times_each_philo_must_eat = -1;
		(*philo_array)[i].right_fork = &(common->mutex_fork[i]);
		(*philo_array)[i].left_fork = &(common->mutex_fork[(i + 1)
				% num_philo]);
		(*philo_array)[i].right_fork_bool = &(common->bool_fork[i]);
		(*philo_array)[i].left_fork_bool = &(common->bool_fork[i - 1]);
		common->which_eat[i] = 0;
		if (i % 2 == 0)
		{
			(*philo_array)[i].which_eat = &(common->which_eat[i]);
			(*philo_array)[i].mutex_which_eat = &(common->mutex_which_eat[i]);
		}
		else
		{
			(*philo_array)[i].which_eat = &(common->which_eat[i - 1]);
			(*philo_array)[i].mutex_which_eat = &(common->mutex_which_eat[i
					- 1]);
		}
		(*philo_array)[i].mutex_last_eat = &(common->mutex_last_eat[i]);
		(*philo_array)[i].mutex_die = &(common->mutex_die[i]);
		(*philo_array)[i].num_full_philo = common->num_full_philo;
		(*philo_array)[i].num_eat = 0;
		(*philo_array)[i].someone_dead = common->someone_dead;
		(*philo_array)[i].is_eat_finish = common->is_eat_finish;
		(*philo_array)[i].mutex_eat = common->mutex_eat;
		// (*philo_array)[i].mutex_died = common->mutex_died;
		(*philo_array)[i].mutex_write = common->mutex_write;
		(*philo_array)[i].thread[0] = (pthread_t)NULL;
		i += 1;
	}
}

void	initialize_overall(char *argv[], t_common *common,
		t_philosopher **philo_array)
{
	int	num_philo;
	int	i;

	num_philo = ft_atoi(argv[1]);
	common->bool_fork = (bool *)malloc(sizeof(bool) * num_philo);
	common->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	common->mutex_die = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* num_philo);
	common->last_eat = (size_t *)malloc(sizeof(size_t) * num_philo);
	common->num_philo = num_philo;
	common->time_to_die = ft_atoi(argv[2]);
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
		common->bool_fork[i] = false;
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
	// pthread_mutex_init(&(common->mutex_died[0]), NULL);
}

void	initialize_main(int argc, char *argv[], t_philosopher **philo_array,
		t_common *common)
{
	initialize_overall(argv, common, philo_array);
	initialize_mutex(argv, common);
	initialize_thread(argc, argv, philo_array, common);
}
