/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:49:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/05 15:04:56 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		parser(t_param *param, char **argv)
{
	param->number = ft_atoi(argv[1]);
	param->ttdie = ft_atoi(argv[2]);
	param->tteat = ft_atoi(argv[3]);
	param->ttsleep = ft_atoi(argv[4]);
	if (argv[5])
		param->cycles = ft_atoi(argv[5]);
	else
		param->cycles = -1;
}

void		print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->param->block_print);
	if (!ft_strcmp(msg, "cycles ended"))
	{
		ft_putnbr(philo->param->cycles);
		write(1, " ", 1);
		ft_putstr(msg);
		write(1, "\n", 1);
		exit(0);
	}
	ft_putnbr(get_time() - philo->param->start_sim);
	write(1, " ", 1);
	ft_putnbr(philo->index + 1);
	write(1, " ", 1);
	ft_putstr(msg);
	write(1, "\n", 1);
	if (!ft_strcmp(msg, "died"))
		exit(0);
	pthread_mutex_unlock(&philo->param->block_print);
}

long long	get_time(void)
{
	struct timeval	time;
	long long		milisec;

	gettimeofday(&time, NULL);
	milisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milisec);
}

void		summon_philosophium(t_philo *philo, int q)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < philo[0].param->number)
	{
		if (i % 2 == q)
		{
			philo[i].last_eating = get_time();
			pthread_create(&thread, NULL, eating, (void *)&philo[i]);
			pthread_detach(thread);
		}
		i++;
	}
}

int			ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (!s1[i] || !s2[i])
		return (s1[i] - s2[i]);
	return (0);
}
