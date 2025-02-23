#include "../include/philosopher.h"

bool	is_within_int(char *nptr)
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
		if (pm == 1 && (ans > INT_MAX / 10 || ((INT_MAX - ans * 10) < (*nptr
						- '0'))))
			return (false);
		if (ans != 0 && pm == -1 && ((ans > -1 * (INT_MIN / 10)) || (-1
					* (INT_MIN + ans * 10)) < (*nptr - '0')))
			return (false);
		ans = ans * 10 + (*nptr - '0');
		nptr += 1;
	}
	return (true);
}

bool	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (false);
		i += 1;
	}
	return (true);
}

bool	error_main(int argc, char *argv[])
{
	size_t	i;

	if (argc != 5 && argc != 6)
	{
		printf("many or less argument\n");
		return (true);
	}
	i = 1;
	while (i < argc)
	{
		if (is_numeric(argv[i]) == false)
		{
			printf("argument is not numeric or minus value\n");
			return (true);
		}
		if (is_numeric(argv[i]) == false)
		{
			printf("argument is over int range\n");
			return (true);
		}
		i += 1;
	}
	return (false);
}
