# Practice projects: philosophers
The goal of this project it to solve [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in three ways using mutexes, semaphores, threads, processes. 

#### Command to compile and run (Linux only):
`make`<br />
`./philo_[one/two/three] [number_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] ` <br />
as example `./philo_one 5 800 200 200`

#### Solutions:
1. philo_one: Philosophers are threads, forks are mutexes
2. philo_two: Philosophers are threads, forks are semaphor
3. philo_three: Philosophers are processes, forks are semaphor
