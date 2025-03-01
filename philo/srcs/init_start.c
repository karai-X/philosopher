/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:54:04 by karai             #+#    #+#             */
/*   Updated: 2025/02/25 23:58:58 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	initialize_thread_part1(t_philosopher **philo_array, t_common *common,
		int i, int num_philo)
{
	(*philo_array)[i].idx = i + 1;
	(*philo_array)[i].num_philo = num_philo;
	(*philo_array)[i].right_fork = &(common->mutex_fork[i]);
	(*philo_array)[i].left_fork = &(common->mutex_fork[(i + 1) % num_philo]);
	common->which_eat[i] = 0;
	if (i % 2 == 0)
	{
		(*philo_array)[i].which_eat = &(common->which_eat[i]);
		(*philo_array)[i].mutex_which_eat = &(common->mutex_which_eat[i]);
	}
	else
	{
		(*philo_array)[i].which_eat = &(common->which_eat[i - 1]);
		(*philo_array)[i].mutex_which_eat = &(common->mutex_which_eat[i - 1]);
	}
	(*philo_array)[i].mutex_last_eat = &(common->mutex_last_eat[i]);
	(*philo_array)[i].mutex_die = &(common->mutex_die[i]);
	(*philo_array)[i].num_full_philo = common->num_full_philo;
	(*philo_array)[i].num_eat = 0;
	(*philo_array)[i].someone_dead = common->someone_dead;
	(*philo_array)[i].is_eat_finish = common->is_eat_finish;
	(*philo_array)[i].mutex_eat = common->mutex_eat;
	(*philo_array)[i].mutex_write = common->mutex_write;
	(*philo_array)[i].thread[0] = (pthread_t)(NULL);
}

void	initialize_thread(int argc, char *argv[], t_philosopher **philo_array,
		t_common *common)
{
	int	num_philo;
	int	i;

	num_philo = ft_atoi(argv[1]);
	i = 0;
	while (i < num_philo)
	{
		(*philo_array)[i].last_eat = &(common->last_eat[i]);
		(*philo_array)[i].time_to_die = ft_atoi(argv[2]);
		(*philo_array)[i].time_to_eat = ft_atoi(argv[3]);
		(*philo_array)[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			(*philo_array)[i].num_times_each_philo_must_eat = ft_atoi(argv[5]);
		else
			(*philo_array)[i].num_times_each_philo_must_eat = -1;
		initialize_thread_part1(philo_array, common, i, num_philo);
		i += 1;
	}
}

void	initialize_start_time(char *argv[], t_philosopher **philo_array,
		t_common *common)
{
	int		num_philo;
	int		i;
	size_t	start_time;

	num_philo = ft_atoi(argv[1]);
	i = 0;
	start_time = get_time();
	common->start_time = start_time;
	while (i < num_philo)
	{
		(*philo_array)[i].start_time = start_time;
		common->last_eat[i] = start_time;
		i += 1;
	}
}
