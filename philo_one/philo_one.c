/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <student.21-school.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:11:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/01 18:53:03 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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

void start_simulation(t_philo *philo, int num)
{
    int i = 0;
    while(i < num)
    {
       pthread_create(&(philo[i].thread), NULL, eating, (void *)&philo[i]);
       i++;
    }
    // бесконечный цикл в основном потоке на проверку на смерть (каждого по очереди)
}

void *eating(void *tmp)
{
	t_philo *philo = (t_philo *)tmp;
    long long time = get_time();
    philo->last_eating = time;
    printf("%lld   %d   is eating\n", time - philo->start_sim, philo->number + 1);
    usleep(200 * 1000);
    sleeping(philo);
	return NULL;
 
}
void sleeping(t_philo *philo)
{
    long long time = get_time();
    printf("%lld   %d   is sleeping\n", time - philo->start_sim, philo->number + 1);
    usleep(200 * 1000);
    thinking(philo);
}
void thinking(t_philo *philo)
{
    long long time = get_time();
    printf("%lld   %d   is thinking\n", time - philo->start_sim, philo->number + 1);
    usleep(200 * 1000);
    eating(philo);
}


void philo_init(t_philo *philo, t_param param)
{
    // добавить вилки и раздать философам!
    int i = 0;
    while(i < param.number)
    {
        philo[i].number = i;
        philo[i].start_sim = get_time();
        philo[i].last_eating = philo[i].start_sim;
        philo[i].ttDie = param.ttDie;
        philo[i].ttEat = param.ttEat;
        philo[i].ttSleep = param.ttSleep;
        philo[i].cycles = param.cycles;
        i++;
    }
}

int main(int argc, char **argv)
{
    t_param param;

	if (argc < 5 || argc > 6)
    {
        write(2, "Need args", 9);
        return (1);
    }
    parser(&param, argv);
    t_philo philo[param.number];
    philo_init(philo, param);
	// printf("%d %d %d %d\n", philo[0].number, philo[1].number, philo[2].number, philo[3].number);
   	start_simulation(philo, param.number);
	while (1)
		usleep(200);
    // TO DO: заполнить массив философов - время последнего поеда(на старте это время старта симуляции)
    // два указателя на мьютексы-вилки + инициализировать их
    // создание тредов и они будут стартовать в бесконечном цикле еды/спанья/думанья
    // там же бесконечный цикл проверки не умер ли кто
    // + мьютекс на печать, в случае смерти блок печати, очистка памяти и выход

    return (0);
}