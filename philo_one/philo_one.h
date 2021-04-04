/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:12:00 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/04 03:52:41 by ppipes           ###   ########.fr       */
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
    // long long		start_sim;
	int				index;
}               t_philo;

void parser(t_param *param, char **argv);
long long get_time(void);
void start_simulation(t_philo *philo);
void *eating(void *tmp);
void sleeping_thinking(t_philo *philo);
void philo_init(t_philo *philo, pthread_mutex_t *forks, t_param *param);
int			ft_atoi(const char *nptr);
void		ft_putnbr_fd(int n, int fd);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void print_msg(int time, int index, char *msg, pthread_mutex_t	*block_print);

#endif