/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 01:18:05 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/07 01:24:02 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	living(t_philo *philo)
{
	pthread_t thread;

	pthread_create(&thread, NULL, eating, (void *)philo);
	pthread_detach(thread);
	while (1)
	{
		sem_wait(philo->param->block_dying);
		if (get_time() - philo->last_eating > philo->param->ttdie)
			print_msg(philo, "died");
		sem_post(philo->param->block_dying);
	}
}

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
	if (philo->param->cycles > 0 && philo->eat_count == philo->param->cycles)
		exit(0);
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

void	print_msg(t_philo *philo, char *msg)
{
	sem_wait(philo->param->block_print);
	ft_putnbr(get_time() - philo->param->start_sim);
	write(1, " ", 1);
	ft_putnbr(philo->index + 1);
	write(1, " ", 1);
	ft_putstr(msg);
	write(1, "\n", 1);
	if (!ft_strcmp(msg, "died"))
	{
		sem_post(philo->param->block_print);
		exit(1);
	}
	sem_post(philo->param->block_print);
}
