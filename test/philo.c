#include <pthread.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PH_SIZE 5

typedef struct s_philo  // name and forks numbers
{
	char *name;
	int left_fork;
	int right_fork;
}				t_philo;

typedef struct s_table // table with forks-mutex
{
	pthread_mutex_t forks[PH_SIZE];
}				t_table;

typedef struct s_philo_args // struct philo + table
{
	t_philo *philo;
	t_table *table;
}				t_philo_args;

pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;

void	philo_init(t_philo *philo, char *name, int left_fork, int right_fork)
{
	philo->name = name;
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
}

void table_init(t_table *table)
{
	int i;

	i = 0;
	while(i < PH_SIZE)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	*eat(void *args)
{
	t_philo_args *arg = (t_philo_args *)args;
	t_philo *philo = arg->philo;
	t_table *table = arg->table;

	while (1)
	{
		printf("%s started dinner\n", philo->name);
		pthread_mutex_lock(&entry_point);
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		usleep(1000);
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		pthread_mutex_unlock(&entry_point);
		printf("%s is eating after %d ms sleep\n", philo->name, rand);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		printf("%s finished dinner\n", philo->name);
	}
}

int	main(void)
{
	pthread_t threads[PH_SIZE];
	t_philo philosophers[PH_SIZE];
	t_philo_args arguments[PH_SIZE];
	t_table table;
	int i;

	table_init(&table);
	philo_init(&philosophers[0], "Fluttershy", 0, 1);
	philo_init(&philosophers[1], "Pinky Pie", 1, 2);
	philo_init(&philosophers[2], "Applejack", 2, 3);
	philo_init(&philosophers[3], "Rarity", 3, 4);
	philo_init(&philosophers[4], "Twilight Sparkle", 4, 0);

	i = 0;
	while(i < PH_SIZE)
	{
		arguments[i].philo = &philosophers[i];
		arguments[i].table = &table;
		i++;
	}
	i = 0;
	while(i < PH_SIZE)
	{
		pthread_create(&threads[i], NULL, eat, &arguments[i]);
		i++;
	}
	i = 0;
	while(i < PH_SIZE)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	// wait();
}