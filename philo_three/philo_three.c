/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:11:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/07 01:23:27 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	waiting_killing(t_philo *philo)
{
	int	status;
	int	i;

	status = 0;
	i = philo->param->number;
	while (status == 0 && i > 0)
	{
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		i--;
	}
	i = 0;
	while (i < philo->param->number)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}

void	start_simulation(t_philo *philo)
{
	int	i;

	philo[0].param->start_sim = get_time();
	i = 0;
	while (i < philo[0].param->number)
	{
		philo[i].last_eating = get_time();
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			living(&philo[i]);
		i++;
	}
	waiting_killing(philo);
}

void	philo_init(t_param *param)
{
	int				i;
	t_philo			philo[param->number];

	i = 0;
	sem_unlink("/forks");
	sem_unlink("/waiter");
	sem_unlink("/print");
	sem_unlink("/dying");
	param->forks = sem_open("/forks", O_CREAT, O_RDWR, param->number);
	param->waiter = sem_open("/waiter", O_CREAT, O_RDWR, 1);
	param->block_print = sem_open("/print", O_CREAT, O_RDWR, 1);
	param->block_dying = sem_open("/dying", O_CREAT, O_RDWR, 1);
	i = 0;
	while (i < param->number)
	{
		philo[i].index = i;
		philo[i].param = param;
		philo[i].eat_count = 0;
		i++;
	}
	start_simulation(philo);
}

void	parser(t_param *param, char **argv)
{
	param->number = ft_atoi(argv[1]);
	param->ttdie = ft_atoi(argv[2]);
	param->tteat = ft_atoi(argv[3]);
	param->ttsleep = ft_atoi(argv[4]);
	if (argv[5])
		param->cycles = ft_atoi(argv[5]);
	else
		param->cycles = -1;
	if (param->number < 2 || param->number > 200 || param->ttdie < 1
	|| param->tteat < 1 || param->ttsleep < 1)
		exit(1);
}

int		main(int argc, char **argv)
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
