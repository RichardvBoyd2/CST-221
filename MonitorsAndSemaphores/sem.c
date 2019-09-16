/*Richard Boyd
Monitors and Semaphores
This one uses a Semaphore to solve the Producer and Consumer problem
*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

//compile with -lpthread -lrt

#define N 10
int buffer[11];
int count = 0;
int product = 1;
sem_t sem;

void put(int i)
{
	printf("put: %d\n", i);
	buffer[count] = i;
}

int get()
{
	int result = buffer[count];
	buffer[count] = 0;
	return result;
}

int produce()
{
	return product++;
}

void consume(int i)
{
	printf("consume: %d\n", i);
}

void* producer()
{
	int i;
	
	while (1)
	{
		if (count < N)
		{
			sem_wait(&sem);
			i = produce();
			put(i);
			count++;
			sem_post(&sem);
		}
	}
}

void* consumer()
{
	int i;
	
	while (1)
	{
		if (count > 0)
		{
			sem_wait(&sem);
			count = count - 1;
			i = get();
			consume(i);
			sem_post(&sem);	
		}		
	}
}

int main(void)
{
	sem_init(&sem, 0, 1);
	pthread_t pro, con;
	pthread_create(&pro, NULL, producer, NULL);
	pthread_create(&con, NULL, consumer, NULL);
	pthread_join(pro, NULL);
	pthread_join(con, NULL);
	
	return 0;
}