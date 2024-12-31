/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:24:32 by karai             #+#    #+#             */
/*   Updated: 2024/12/31 17:29:21 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				idx;
	int				num_philo;
	size_t			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_each_philo_must_eat;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	bool			*right_fork_bool;
	bool			*left_fork_bool;
}					t_philosopher;

typedef struct s_common
{
	pthread_mutex_t	*mutex_fork;
	bool			*bool_fork;
}					t_common;

int					ft_atoi(char *nptr);

void				initialize_main(int argc, char *argv[],
						t_philosopher **philo_array, t_common *common);
void				initialize_overall(char *argv[], t_common *common);
void				initialize_thread(int argc, char *argv[],
						t_philosopher **philo_array, t_common *common);
size_t				get_time(void);

void				*loop_philo(void *arg);
void				print_custom(char *str, t_philosopher philo);

#endif
