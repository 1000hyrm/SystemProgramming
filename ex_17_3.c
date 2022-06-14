#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define num 3

void *func(void *arg){
	char *s = (char *)arg;
	long unsigned int val;
	val = atoi(s);
	val = val + 3;
	pthread_exit((void *)val);
	pthread_exit(s);
}

int main(){
	pthread_t t1[3];
	void *rt;
	int res;
	
	pthread_create(&t1[0], NULL, func, "3");
	pthread_create(&t1[1], NULL, func, "5");
	pthread_create(&t1[2], NULL, func, "6");
	
	pthread_join(t1[0], (void**)&res);
	printf("thread exited with %d\n", res);
	
	pthread_join(t1[1], (void **)&res);
	printf("thread exited with %d\n", res);
	
	pthread_join(t1[2], (void **)&res);
	printf("thread exited with %d\n", res);

}

