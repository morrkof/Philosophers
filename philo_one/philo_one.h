/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:12:00 by ppipes            #+#    #+#             */
/*   Updated: 2021/03/31 23:52:37 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_param
{
    int         number;
    int         ttDie;
    int         ttEat;
    int         ttSleep;
    int         cycles;
}               t_param;

typedef struct s_philo
{
    pthread_t   thread;
    int         number;
    long long   last_eating;
    long long   start_sim;
}               t_philo;

void parser(t_param *param, char **argv);
long long get_time(void);
void start_simulation(t_philo *philo, int num);
void *eating(void *tmp);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);
void philo_init(t_philo *philo, int num);

#endif