/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <student.21-school.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:11:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/03/30 16:44:19 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_philo
{
    int         number;
    int         ttDie;
    int         ttEat;
    int         ttSleep;
    int         cycles;
}               t_philo;

#include "philo_one.h"

void parser(t_philo *philo, char **argv)
{
    philo->number = atoi(argv[1]);
    philo->ttDie = atoi(argv[2]);
    philo->ttEat = atoi(argv[3]);
    philo->ttSleep = atoi(argv[4]);
    if (argv[5])
        philo->cycles = atoi(argv[5]);
    else
        philo->cycles = -1;
}

int main(int argc, char **argv)
{
    t_philo philo;

	if (argc < 5 || argc > 6)
    {
        write(2, "Need args", 9);
        return (1);
    }
    parser(&philo, argv);
    // printf("Numbers of philo = %d\ntime to die = %d\ntime to eat = %d\ntime to sleep = %d\ncycles = %d", 
    // philo.number, philo.ttDie, philo.ttEat, philo.ttSleep, philo.cycles);

    

    return (0);
}