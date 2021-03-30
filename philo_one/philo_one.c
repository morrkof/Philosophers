/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:11:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/03/31 00:26:16 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    int         last_eating;
}               t_philo;

#include "philo_one.h"



void parser(t_param *param, char **argv)
{
	// заменить атои на самописный!
    param->number = atoi(argv[1]);
    param->ttDie = atoi(argv[2]);
    param->ttEat = atoi(argv[3]);
    param->ttSleep = atoi(argv[4]);
    if (argv[5])
        param->cycles = atoi(argv[5]);
    else
        param->cycles = -1;
}



long long get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    long long milisec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return milisec;
}


void eating(t_philo *philo)
{
    long long time = get_time();

}
void sleeping(t_philo *philo);
void thinking(t_philo *philo);




int main(int argc, char **argv)
{
    t_param param;

	if (argc < 5 || argc > 6)
    {
        write(2, "Need args", 9);
        return (1);
    }
    parser(&param, argv);
    get_time(); //  где-то запомнить - это время старта симуляции
    t_philo philo[param.number]; 
    // TO DO: заполнить массив философов - время последнего поеда(на старте это время старта симуляции)
    // два указателя на мьютексы-вилки + инициализировать их
    // создание тредов и они будут стартовать в бесконечном цикле еды/спанья/думанья
    // там же бесконечный цикл проверки не умер ли кто

    return (0);
}