/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 02:47:23 by karai             #+#    #+#             */
/*   Updated: 2024/12/31 14:19:40 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(char *nptr)
{
	long	ans;
	int		pm;

	ans = 0;
	pm = 1;
	while (*nptr == '\f' || *nptr == '\n' || *nptr == '\r' || *nptr == '\t'
		|| *nptr == '\v' || *nptr == ' ')
		nptr += 1;
	if (*nptr == '-')
		pm = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr += 1;
	while (*nptr <= '9' && *nptr >= '0')
	{
		if (pm == 1 && (ans > LONG_MAX / 10 || ((LONG_MAX - ans * 10) < (*nptr
						- '0'))))
			return ((int)LONG_MAX);
		if (ans != 0 && pm == -1 && ((ans > -1 * (LONG_MIN / 10)) || (-1
					* (LONG_MIN + ans * 10)) < (*nptr - '0')))
			return ((int)LONG_MIN);
		ans = ans * 10 + (*nptr - '0');
		nptr += 1;
	}
	return (ans * pm);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
