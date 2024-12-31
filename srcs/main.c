/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:21:21 by karai             #+#    #+#             */
/*   Updated: 2024/12/31 16:13:42 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*thread_function(void *arg)
{
	int	*int_arg;

	int_arg = (int *)arg;
	while (*int_arg < 30)
	{
		printf("do something %d\n", *int_arg);
		*int_arg += 1;
	}
}

int	main(int argc, char *argv[])
{
	t_philosopher	*philo_array;
	t_common		common[1];
	int				i;

	if (argc != 5 && argc != 6)
	{
		return (1);
	}
	write(1, "a\n", 2);
	initialize_main(argc, argv, philo_array, common);
	i = 0;
	while (i < philo_array[0].num_philo)
	{
		pthread_create(&(philo_array[i].thread), NULL, &loop_philo,
			(void *)(&(philo_array[i])));
		i += 1;
	}
	// i = 0;
	// while (i < philo_num)
	// {
	// 	pthread_join(thread[i], NULL);
	// 	i += 1;
	// }
	// pthread_t	thread;
	// void		*retval;
	// // スレッドを作成
	// if (pthread_create(&thread, NULL, do_something, NULL) != 0)
	// 	// エラー処理
	// 	return (0);
	// // スレッドの終了方法
	// // 1. スレッドが終了するまで待つ
	// pthread_join(thread, &retval);
	// // 2. スレッドを待たない
	// pthread_detach(thread);
}
