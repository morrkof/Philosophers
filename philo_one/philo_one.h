/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:12:00 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/04 14:53:00 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_param
{
    int         number;
    int         ttDie;
    int         ttEat;
    int         ttSleep;
    int         cycles;
	long long		start_sim;
	pthread_mutex_t	block_print;
}               t_param;

typedef struct s_philo
{
	t_param			*param;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
    long long		last_eating;
	int				index;
	int				eat_count;
}               t_philo;

void parser(t_param *param, char **argv);
long long get_time(void);
void start_simulation(t_philo *philo);
void *eating(void *tmp);
void sleeping_thinking(t_philo *philo);
void philo_init(t_param *param);
int			ft_atoi(const char *nptr);
void		ft_putnbr(int n);
void	ft_putstr(char *s);
size_t	ft_strlen(const char *s);
void print_msg(t_philo *philo, char *msg);
void	summon_philosophium(t_philo *philo, int Q);

#endif