#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int CNT = 0;

void *func(void* arg){
	char *s = (char *)arg;
	
	printf("thread said : %s\n", s);
	sleep(1);
	
	int i;
	i = atoi(s);
	
	printf("after sleep : %d\n", i*i);
	
	//pthread_exit(s);
}

int main(int argc, char *argv[]){
	
	for(int i=1; i<argc; i++){
		CNT++;
	}
	printf("CNT = %d\n", CNT);	
	pthread_t t1[CNT];
	
	for(int j=0; j<CNT; j++){
		pthread_create(&t1[j], NULL, func, argv[j+1]);
	}
	
	for(int k=0; k<CNT; k++){
		pthread_join(t1[k], NULL);
	}
	
	printf("counter value %d\n", CNT);
}
	
