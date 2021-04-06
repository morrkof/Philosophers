/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:11:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/06 13:42:08 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*eating(void *tmp)
{
	t_philo			*philo;

	philo = (t_philo *)tmp;
	sem_wait(philo->param->waiter);
	sem_wait(philo->param->forks);
	print_msg(philo, "has taken a left fork");
	sem_wait(philo->param->forks);
	sem_post(philo->param->waiter);
	sem_wait(philo->param->block_dying);
	print_msg(philo, "has taken a right fork");
	print_msg(philo, "is eating");
	philo->last_eating = get_time();
	sem_post(philo->param->block_dying);
	usleep(philo->param->tteat * 1000);
	sem_post(philo->param->forks);
	sem_post(philo->param->forks);
	philo->eat_count += 1;
	sleeping_thinking(philo);
	return (NULL);
}

void	sleeping_thinking(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	usleep(philo->param->ttsleep * 1000);
	print_msg(philo, "is thinking");
	eating(philo);
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
			sem_wait(philo->param->block_dying);
			if (get_time() - philo[i].last_eating > philo[0].param->ttdie)
				print_msg(&philo[i], "died");
			sem_post(philo->param->block_dying);
			if (philo[i].eat_count < philo[0].param->cycles)
				end_flag = 0;
			i++;
		}
		if (end_flag && philo[0].param->cycles > 0)
			print_msg(&philo[0], "cycles ended");
	}
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
