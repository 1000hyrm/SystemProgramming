/*  main thread는 동일한 기능을 수행하는 3개의 thread를 실행하며, 이때, 
     실행되는 각 thread의 argument로는 임의의 integer 값(이 값을 a라 한다.)을 기술한다.
    수행되는 각 thread는 argument로 입력된 integer 값에 3을 더한 값을 pthread_exit 함수의 파라메타로 기술한다.
    main thread는 자신이 수행한 모든 thread들이 종료하기를 기다리며, 각 thread가 종료하면 종료한 thread가 pthread_exit에서 기술한 값을 출력한다. (결국 a+3 값이 출력된다.)*/

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

