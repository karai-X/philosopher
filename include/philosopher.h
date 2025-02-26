/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:24:32 by karai             #+#    #+#             */
/*   Updated: 2025/02/27 00:57:02 by karai            ###   ########.fr       */
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
# define FINISH 3

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
	pthread_t		thread[1];
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	*mutex_die;
	pthread_mutex_t	*mutex_eat;
	pthread_mutex_t	*mutex_which_eat;
	pthread_mutex_t	*mutex_last_eat;
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
	pthread_mutex_t	mutex_eat[1];
	int				*which_eat;
	pthread_mutex_t	*mutex_which_eat;
	size_t			*last_eat;
	pthread_mutex_t	*mutex_last_eat;
	int				num_philo;
	size_t			time_to_die;
	size_t			start_time;
	t_philosopher	*philo_array;
	int				num_full_philo[1];
	bool			someone_dead[1];
	bool			is_eat_finish[1];
}					t_common;

// main.c
void				thread_create_philo(t_philosopher *philo_array);

int					ft_atoi(char *nptr);

// init.c
void				initialize_main(int argc, char *argv[],
						t_philosopher **philo_array, t_common *common);
void				initialize_overall(char *argv[], t_common *common,
						t_philosopher **philo_aray);
void				initialize_mutex(char *argv[], t_common *common);

// init_thread.c
void				initialize_thread(int argc, char *argv[],
						t_philosopher **philo_array, t_common *common);
void				initialize_thread_part1(t_philosopher **philo_array,
						t_common *common, int i, int num_philo);
void				initialize_start_time(char *argv[],
						t_philosopher **philo_array, t_common *common);

size_t				get_time(void);

void				*loop_philo(void *arg);
bool				sleeping(t_philosopher *philo);
bool				thinking(t_philosopher *philo);
bool				print_custom(char *str, t_philosopher *philo);
void				print_custom_time(char *str, t_philosopher philo,
						size_t current_time);
void				eating(t_philosopher *philo);

// eating.c
bool				is_finish_in_eating(t_philosopher *philo,
						pthread_mutex_t *rl_fork);
void				taken_fork(t_philosopher *philo, pthread_mutex_t *lr_fork);
void				eating_part(t_philosopher *philo);
bool				eating_mainpart(t_philosopher *philo, int rl_which_eat,
						pthread_mutex_t *lr_fork);

// monitor.c
void				*monitor(void *arg);
bool				monitor_died(t_common *common, int i);

void				*waiter(void *arg);

// error.c
bool				is_within_int(char *nptr);
bool				is_numeric(char *str);
bool				error_main(int argc, char *argv[]);

// free.c
void				free_common(t_common *common);
void				destroy(t_common *common);
void				join_all(t_philosopher *philo_array,
						pthread_t monitor_thread, pthread_t *waiter_thread,
						int num_philo);

#endif
