/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:11:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/04 15:50:05 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->param->block_print);
	ft_putnbr(get_time() - philo->param->start_sim);
	write(1, " ", 1);
	ft_putnbr(philo->index + 1);
	write(1, " ", 1);
	ft_putstr(msg);
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->param->block_print);
}

void	parser(t_param *param, char **argv)
{
	param->number = ft_atoi(argv[1]);
	param->ttDie = ft_atoi(argv[2]);
	param->ttEat = ft_atoi(argv[3]);
	param->ttSleep = ft_atoi(argv[4]);
	if (argv[5])
		param->cycles = ft_atoi(argv[5]);
	else
		param->cycles = -1;
}

long long	get_time(void)
{
	struct timeval	time;
	long long		milisec;

	gettimeofday(&time, NULL);
	milisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milisec);
}

void	summon_philosophium(t_philo *philo, int Q)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < philo[0].param->number)
	{
		if (i % 2 == Q)
		{
			philo[i].last_eating = get_time();
			pthread_create(&thread, NULL, eating, (void *)&philo[i]);
			pthread_detach(thread);
		}
		i++;
	}
}

void	start_simulation(t_philo *philo)
{
	int			i;
	int			end_flag;

	philo[0].param->start_sim = get_time();
	summon_philosophium(philo, 0);
	usleep(1 * 1000);
	summon_philosophium(philo, 1);
	while (1)
	{
		i = 0;
		end_flag = 1;
		while (i < philo[0].param->number)
		{
			if (get_time() - philo[i].last_eating > philo[0].param->ttDie)
			{
				print_msg(&philo[i], "died");
				exit(0);
			}
			if (philo[i].eat_count < philo[0].param->cycles)
				end_flag = 0;
			i++;
		}
		if (end_flag && philo[0].param->cycles > 0)
			exit(0);
		// usleep(5 * 1000);
	}
}

void	*eating(void *tmp)
{
	t_philo			*philo;
	// pthread_mutex_t	*first_fork;
	// pthread_mutex_t	*second_fork;

	philo = (t_philo *)tmp;
	// first_fork = philo->left_fork;
	// second_fork = philo->right_fork;
	// if (philo->left_fork > philo->right_fork)
	// {
	// 	first_fork = philo->right_fork;
	// 	second_fork = philo->left_fork;
	// }
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a left fork");
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a right fork");
	print_msg(philo, "is eating");
	philo->last_eating = get_time();
	usleep(philo->param->ttEat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->eat_count += 1;
	sleeping_thinking(philo);
	return (NULL);
}

void	sleeping_thinking(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	usleep(philo->param->ttSleep * 1000);
	print_msg(philo, "is thinking");
	eating(philo);
}

void	philo_init(t_param *param)
{
	int				i;
	t_philo			philo[param->number];
	pthread_mutex_t	forks[param->number];

	i = 0;
	pthread_mutex_init(&param->block_print, NULL);
	while (i < param->number)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < param->number)
	{
		philo[i].left_fork = &forks[(i + 1) % param->number];
		philo[i].right_fork = &forks[i];
		philo[i].index = i;
		philo[i].param = param;
		philo[i].eat_count = 0;
		i++;
	}
	start_simulation(philo);
}

int	main(int argc, char **argv)
{
	t_param param;

	if (argc < 5 || argc > 6)
	{
		write(2, "Need args", 9);
		return (1);
	}
	parser(&param, argv);
	philo_init(&param);
	return (0);
}
