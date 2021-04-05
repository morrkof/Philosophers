/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:12:00 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/05 14:58:12 by ppipes           ###   ########.fr       */
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

typedef struct		s_param
{
	int				number;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				cycles;
	long long		start_sim;
	pthread_mutex_t	block_print;
}					t_param;

typedef struct		s_philo
{
	t_param			*param;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	block_dying;
	long long		last_eating;
	int				index;
	int				eat_count;
}					t_philo;

void				parser(t_param *param, char **argv);
void				philo_init(t_param *param);
void				start_simulation(t_philo *philo);
void				summon_philosophium(t_philo *philo, int q);
void				*eating(void *tmp);
void				sleeping_thinking(t_philo *philo);
void				print_msg(t_philo *philo, char *msg);
long long			get_time(void);
int					ft_strcmp(char *s1, char *s2);
size_t				ft_strlen(const char *s);
void				ft_putstr(char *s);
void				ft_putnbr(int n);
int					ft_atoi(const char *nptr);

#endif
