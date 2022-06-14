#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *func(void *arg){
	char *ret;
	printf("thread said : this is thread\n");
	sleep(1);
	pthread_exit(0);
}

int main(){
	pthread_t t1;
	int res, s;
	
	if(pthread_create(&t1, NULL, func, "this is thread") != 0)
		printf("pthread_create error\n");
	
	printf("message from main()\n");
	
	if(pthread_join(t1, (void **)&res) != 0)
		printf("pthread_join error\n");
	else
		printf("main said : ok\n");
	
	exit(EXIT_SUCCESS);
}
