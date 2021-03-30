// #include <pthread.h>
// #include <stdio.h>

// int count; /* общие данные для потоков */

// void *potok(void *param)
// {
// 	int i, upper = atoi(param);
// 	count = 0;

// 	if (upper > 0) {
// 		for (i = 1; i <= upper; i++)
// 		count += i;
// 	}
// 	pthread_exit(0);
// }

// int main(int argc, char *argv[])
// {
//   pthread_t tid; /* идентификатор потока */
//   pthread_attr_t attr; /* отрибуты потока */

// 	pthread_attr_init(&attr); /* получаем дефолтные значения атрибутов */
// 	pthread_create(&tid,&attr,potok,argv[1]); /* создаем новый поток */
// 	pthread_join(tid,NULL); /* ждем завершения исполнения потока */
// 	printf("count = %d\n",count);
// }
	
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
 
// void* helloWorld(void *args) {
//     printf("Hello from thread!\n");
//     return 0;
// }
 
// int main() {
//     pthread_t thread;
//     int status_addr;
 
//     pthread_create(&thread, NULL, helloWorld, NULL);
//     printf("Hello from main!\n");
//     pthread_join(thread, (void**)&status_addr);
//     printf("joined with address %d\n", status_addr);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
 
typedef struct someArgs_tag 
{
    int 		id;
    const char *msg;
    int 		out;
} 				someArgs_t;
 
void* helloWorld(void *args) 
{
    someArgs_t *arg = (someArgs_t*) args;
 
    if (arg->msg == NULL) 
        return 0;
    printf("%s\n", arg->msg);
    arg->out = strlen(arg->msg);
    return 0;
}
 
#define NUM_THREADS 4
 
int main(void) 
{
    pthread_t	threads[NUM_THREADS];
    int 		status;
    int 		i;
    int 		status_addr;
    someArgs_t	args[NUM_THREADS];
    const char *messages[] = {
        "First",
        NULL,
        "Third Message",
        "Fourth Message"
    };
 
    for (i = 0; i < NUM_THREADS; i++) 
	{
        args[i].id = i;
        args[i].msg = messages[i];
    }
 
    for (i = 0; i < NUM_THREADS; i++) 
	{
        status = pthread_create(&threads[i], NULL, helloWorld, (void*) &args[i]);
        if (status != 0) 
		{
            printf("main error: can't create thread, status = %d\n", status);
            exit(1);
        }
    }
    printf("Main Message\n");
    for (i = 0; i < NUM_THREADS; i++) {
        status = pthread_join(threads[i], (void**)&status_addr);
        if (status != 0) 
		{
            printf("main error: can't join thread, status = %d\n", status);
            exit(1);
        }
        printf("joined with address %d\n", status_addr);
    }
    for (i = 0; i < NUM_THREADS; i++)
        printf("thread %d arg.out = %d\n", i, args[i].out);
    return 0;
}