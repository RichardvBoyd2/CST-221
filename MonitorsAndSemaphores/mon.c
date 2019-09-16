/*Richard Boyd
Monitors and Semaphores
This one uses a Monitor to solve the Producer and Consumer problem
*/

#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>

int product = 1;

struct monitor 
{
	#define N 10
	int count;
	int buffer[11];
	
};

struct monitor mon;

void put(int i)
{
	printf("put: %d\n", i);
	mon.buffer[mon.count] = i;
}

int get()
{
	int result = mon.buffer[mon.count];
	mon.buffer[mon.count] = 0;
	return result;
}

void countUp()
{
	mon.count++;
}

void countDn()
{
	mon.count--;
}

bool isFull()
{
	if(mon.count == N){
		return true;
	} else {
		return false;
	}
}

bool isEmpty()
{
	if(mon.count == 0){
		return true;
	} else {
		return false;
	}
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
	
	while(1)
	{
		if (!(isFull()))
		{
			i = produce();
			put(i);
			countUp();
		}
	}
}

void* consumer()
{
	int i;
	
	while(1)
	{
		if (!(isEmpty()))
		{
			countDn();
			i = get();
			consume(i);
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