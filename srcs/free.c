/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:09:14 by karai             #+#    #+#             */
/*   Updated: 2024/12/23 23:58:28 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free2dim(char **str_array)
{
	size_t	i;

	if (str_array == NULL)
		return ;
	i = 0;
	while (str_array[i])
	{
		free(str_array[i]);
		i += 1;
	}
	free(str_array);
}

void	perror_exit(char *str, char **str_array1, char **str_array2,
		int exit_status)
{
	perror(str);
	free2dim(str_array1);
	free2dim(str_array2);
	exit(exit_status);
}

void	free_exit(char **str_array1, char **str_array2, int exit_status)
{
	free2dim(str_array1);
	free2dim(str_array2);
	exit(exit_status);
}
