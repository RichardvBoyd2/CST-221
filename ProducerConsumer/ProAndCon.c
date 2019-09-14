/*Richard Boyd
Producer and Consumer problem
Demonstrates pacing two threads without use of sychronization techniques
*/

#include<stdio.h>
#include<pthread.h>

#define N 10
int buffer[11];
int count = 0;
int product = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t prod = PTHREAD_COND_INITIALIZER;
pthread_cond_t cons = PTHREAD_COND_INITIALIZER;

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
	
	while(product < 30)
	{
		if (count == N)
		{
			pthread_cond_wait(&prod, &mutex);
		}
		i = produce();
		put(i);
		count++;
		if (count == 1)
		{
			pthread_cond_signal(&cons);			
		}
	}
}

void* consumer()
{
	int i;
	
	while(!(product == 30 && count == 0))
	{
		if (count == 0)
		{
			pthread_cond_wait(&cons, &mutex);
		}
		count = count - 1;
		i = get();
		consume(i);
		
		if (count == N - 1)
		{
			pthread_cond_signal(&prod);			
		}
	}
}

int main(void)
{	
	pthread_t pro, con;
	pthread_create(&pro, NULL, producer, NULL);
	pthread_create(&con, NULL, consumer, NULL);
	pthread_join(pro, NULL);
	pthread_join(con, NULL);
	
	return 0;
}
