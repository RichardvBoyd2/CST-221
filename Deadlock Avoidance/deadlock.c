/*Richard Boyd
Deadlock Avoidance
Uses a timer to manage multiple threads and their attempts to share a single resource
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int N = 10000000;
int resource = 0;
int timerFlag = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* plusOne();
void* plusTwo();
void* plusThree();
void* plusFour();

int main(void)
{
	FILE * fp;
	fp = fopen("test.txt", "w");
	//fprintf(fp, "%s", "Is this working?\n");
	//fprintf(fp, "%s", "Can we do multiple lines?\n");
	
	pthread_t p1, p2, p3, p4;
	pthread_create(&p1, NULL, plusOne, NULL);
	pthread_create(&p2, NULL, plusTwo, NULL);
	pthread_create(&p3, NULL, plusThree, NULL);
	pthread_create(&p4, NULL, plusFour, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	pthread_join(p4, NULL);
	
	fclose(fp);
	return 0;
}

void* timer()
{
	sleep(1);
	timerFlag = 1;
}

void* plusOne()
{
	FILE * fp;
	fp = fopen("test.txt", "a");
	
	while(resource < N)
	{
		pthread_mutex_lock(&mutex);
		fprintf(fp, "%s", "plusOne is running\n");
		pthread_t time;
		pthread_create(&time, NULL, timer, NULL);
		while (1)
		{
			resource = resource + 1;
			printf("\n+ 1 = %d\n", resource);
			
			if (timerFlag)
			{
				break;
			}
		}
		timerFlag = 0;
		pthread_mutex_unlock(&mutex);	
	}
	
}

void* plusTwo()
{
	FILE * fp;
	fp = fopen("test.txt", "a");
	
	while(resource < N)
	{
		pthread_mutex_lock(&mutex);
		fprintf(fp, "%s", "plusTwo is running\n");
		pthread_t time;
		pthread_create(&time, NULL, timer, NULL);
		
		while (1)
		{
			resource = resource + 2;
			printf("\n+ 2 = %d\n", resource);
			if (timerFlag)
			{
				break;
			}
		}
		timerFlag = 0;
		pthread_mutex_unlock(&mutex);
	}
}

void* plusThree()
{
	FILE * fp;
	fp = fopen("test.txt", "a");
	
	while(resource < N)
	{
		pthread_mutex_lock(&mutex);
		fprintf(fp, "%s", "plusThree is running\n");
		pthread_t time;
		pthread_create(&time, NULL, timer, NULL);
		
		while (1)
		{
			resource = resource + 3;
			printf("\n+ 3 = %d\n", resource);
			if (timerFlag)
			{
				break;
			}
		}
		timerFlag = 0;
		pthread_mutex_unlock(&mutex);
	}
	
}

void* plusFour()
{
	FILE * fp;
	fp = fopen("test.txt", "a");
	
	while(resource < N)
	{
		pthread_mutex_lock(&mutex);
		fprintf(fp, "%s", "plusFour is running\n");
		pthread_t time;
		pthread_create(&time, NULL, timer, NULL);
		while (1)
		{
			resource = resource + 4;
			printf("\n+ 4 = %d\n", resource);
			if (timerFlag)
			{
				break;
			}
		}
		timerFlag = 0;
		pthread_mutex_unlock(&mutex);
	}	
}
