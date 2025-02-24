/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:24:32 by karai             #+#    #+#             */
/*   Updated: 2025/02/24 12:57:21 by karai            ###   ########.fr       */
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

# define LEFT_EAT 1
# define RIGHT_EAT 2

typedef struct s_philosopher
{
	int				idx;
	int				num_philo;
	size_t			start_time;
	size_t			*last_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_each_philo_must_eat;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	*mutex_die;
	pthread_mutex_t	*mutex_died;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*mutex_which_eat;
	pthread_mutex_t	*mutex_last_eat;
	bool			*right_fork_bool;
	bool			*left_fork_bool;
	int				num_eat;
	int				*num_full_philo;
	bool			*someone_dead;
	bool			*is_eat_finish;
	int				*which_eat;
}					t_philosopher;

typedef struct s_common
{
	pthread_t		waiter_thread[1];
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_write[1];
	pthread_mutex_t	*mutex_die;
	pthread_mutex_t	mutex_died[1];
	pthread_mutex_t	mutex_eat[1];
	int				*which_eat;
	pthread_mutex_t	*mutex_which_eat;
	bool			*bool_fork;
	size_t			*last_eat;
	pthread_mutex_t	*mutex_last_eat;
	int				num_philo;
	int				time_to_die;
	size_t			start_time;
	t_philosopher	*philo_array;
	int				num_full_philo[1];
	bool			someone_dead[1];
	bool			is_eat_finish[1];
}					t_common;

int					ft_atoi(char *nptr);

void				initialize_main(int argc, char *argv[],
						t_philosopher **philo_array, t_common *common);
void				initialize_overall(char *argv[], t_common *common,
						t_philosopher **philo_aray);
void				initialize_mutex(char *argv[], t_common *common);
void				initialize_thread(int argc, char *argv[],
						t_philosopher **philo_array, t_common *common);

size_t				get_time(void);

void				*loop_philo(void *arg);
void				print_custom(char *str, t_philosopher *philo);
void				print_custom_time(char *str, t_philosopher philo,
						size_t current_time);

void				*monitor(void *arg);

void				*waiter(void *arg);

// error.c
bool				is_within_int(char *nptr);
bool				is_numeric(char *str);
bool				error_main(int argc, char *argv[]);

#endif
