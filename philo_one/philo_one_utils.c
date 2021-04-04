/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:49:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/04 03:52:21 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_putchar_fd(char c, int fd)
{
	// if (fd < 0)
	// 	return ;
	write(fd, &c, 1);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	// if (s == NULL || fd < 0)
	// 	return ;
	i = 0;
	while (s[i] != '\0')
	{
		// ft_putchar_fd(s[i], fd);
		write(fd, &s[i], 1);
		i++;
	}
}

static int	ft_skip_start(const char *nptr, int *minus)
{
	int i;

	i = 0;
	while (nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == '\f' || \
	nptr[i] == '\v' || nptr[i] == '\t' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*minus = -1;
		i++;
	}
	return (i);
}

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *nptr)
{
	int				i;
	int				minus;
	unsigned long	result;

	minus = 1;
	result = 0;
	i = ft_skip_start(nptr, &minus);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (!(ft_isdigit(nptr[i + 1])))
		{
			if (result > LONG_MAX - 1 && minus == -1)
				return (0);
			if (result > LONG_MAX && minus == 1)
				return (-1);
			return (result * minus);
		}
		i++;
	}
	return (0);
}

static void	ft_reverse(char *s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
}

// static void	ft_negative(int *n, int *min, int *minus)
// {
// 	if (*n == -2147483648)
// 	{
// 		*n = *n + 1;
// 		*min = 1;
// 	}
// 	*minus = 1;
// 	*n = *n * -1;
// }

void		ft_putnbr_fd(int n, int fd)
{
	char	s[12];
	int		i;
	// int		minus;
	// int		min;

	i = 0;
	// min = 0;
	// minus = 0;
	if (n == 0)
		ft_putchar_fd('0', fd);
	// if (n < 0)
	// 	ft_negative(&n, &min, &minus);
	while (n > 0)
	{
		s[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	// if (minus)
	// 	s[i++] = '-';
	// if (min)
	// 	s[0] = '8';
	s[i] = '\0';
	ft_reverse(s);
	ft_putstr_fd(s, fd);
}