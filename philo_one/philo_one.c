/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:11:29 by ppipes            #+#    #+#             */
/*   Updated: 2021/04/04 03:52:56 by ppipes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo_one.h"


void print_msg(int time, int index, char *msg, pthread_mutex_t	*block_print)
{
	pthread_mutex_lock(block_print);
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(index, 1);
	write(1, " ", 1);
	ft_putstr_fd(msg, 1);
	write(1, "\n", 1);
	pthread_mutex_unlock(block_print);
}

void parser(t_param *param, char **argv)
{
    param->number = ft_atoi(argv[1]);
    param->ttDie = ft_atoi(argv[2]);
    param->ttEat = ft_atoi(argv[3]);
    param->ttSleep = ft_atoi(argv[4]);
    if (argv[5])
        param->cycles = ft_atoi(argv[5]);
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

void start_simulation(t_philo *philo)
{
    int i = 0;
	pthread_t thread;
	philo[0].param->start_sim = get_time();
    while(i < philo[0].param->number)
    {
		if(!(i % 2))
		{
			philo[i].last_eating = get_time();
    		pthread_create(&thread, NULL, eating, (void *)&philo[i]);
	  		pthread_detach(thread);
			
		}
       	i++;
    }
	i = 0;
	usleep(1 * 1000);
	while(i < philo[0].param->number)
    {
		if(i % 2)
		{
			philo[i].last_eating = get_time();
    		pthread_create(&thread, NULL, eating, (void *)&philo[i]);
	  		pthread_detach(thread);
			
		}
       	i++;
    }
	i = 0;
    while (1)
	{
		i = i % philo[0].param->number;
		if(get_time() - philo[i].last_eating > philo[0].param->ttDie)
		{
			print_msg(get_time() - philo[0].param->start_sim, philo[i].index + 1, "died", &philo->param->block_print);
			// printf("%d eat at %lld\n",philo[i].index + 1,get_time() - philo[i].last_eating);
			// printf("%lld   %d   died\n", get_time() - philo[0].param->start_sim, philo[i].index + 1);
			exit(0);
		}
		i++;
		// usleep(5 * 1000);
	}
}

void *eating(void *tmp)
{
	t_philo *philo = (t_philo *)tmp;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->left_fork > philo->right_fork)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_msg(get_time() - philo->param->start_sim, philo->index + 1, "has taken a left fork", &philo->param->block_print);
	// printf("%lld   %d   has taken a left fork\n", get_time() - philo->param->start_sim, philo->index + 1);
	pthread_mutex_lock(second_fork);
	print_msg(get_time() - philo->param->start_sim, philo->index + 1, "has taken a right fork", &philo->param->block_print);
	// printf("%lld   %d   has taken a right fork\n", get_time() - philo->param->start_sim, philo->index + 1);
    // printf("%d eat at %lld\n",philo->index+1,get_time() - philo->last_eating);
	philo->last_eating = get_time();
	
	print_msg(get_time() - philo->param->start_sim, philo->index + 1, "is eating", &philo->param->block_print);
    // printf("%lld   %d   is eating\n", get_time() - philo->param->start_sim, philo->index + 1);
    usleep(philo->param->ttEat * 1000);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
    sleeping_thinking(philo);
	return NULL;
 
}
void sleeping_thinking(t_philo *philo)
{
    // long long time = get_time();
	print_msg(get_time() - philo->param->start_sim, philo->index + 1, "is sleeping", &philo->param->block_print);
    // printf("%lld   %d   is sleeping\n", time - philo->param->start_sim, philo->index + 1);
    usleep(philo->param->ttSleep * 1000);
 
	print_msg(get_time() - philo->param->start_sim, philo->index + 1, "is thinking", &philo->param->block_print);
    // printf("%lld   %d   is thinking\n", time - philo->param->start_sim, philo->index+ 1);
    // usleep(5 * 1000);
	eating(philo);
}


void philo_init(t_philo *philo, pthread_mutex_t *forks, t_param *param)
{	
    int i = 0;

	pthread_mutex_init(&param->block_print, NULL);
	while(i < param->number)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
    while(i < param->number)
    {
		philo[i].left_fork = &forks[(i + 1) % param->number];
		philo[i].right_fork = &forks[i];
        philo[i].index = i;
        // philo[i].start_sim = get_time();
        // philo[i].last_eating = philo[i].start_sim;
		philo[i].param = param;
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
	pthread_mutex_t forks[param.number];
    philo_init(philo, forks, &param);
   	start_simulation(philo);
	while (1)
		usleep(200);

    return (0);
}