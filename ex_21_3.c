#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *func(void *arg){
	char *s = (char *)arg;
	printf("s = %s\n", s);
	
	int i = atoi(arg);
	printf("i = %d\n", i);
	
	int j = i*i;
	printf("j^2 = %d\n", j);
	
	int *ret;
	ret = &j;
	printf("ret = %p\n", ret);
	printf("ret == %ls\n", ret);
	printf("i = %p\n", &i);
	printf("*ret = %d\n", *ret);
	
	long unsigned int val;
	val = atoi(s);
	val = val*val;
	return ((void *) val);
	//return ((void *) ret);
	//return (ret); //쓰레기값?
	//return ((void) *ret); //error
}

int main(int argc, char *argv[]){
	pthread_t handle;
	char line[256];
	int s, res;
	//void *rt;
	
	if(pthread_create(&handle, NULL, func, argv[1]) != 0){
		perror("pthread_create() error");
		exit(1);
	}
	printf("Thread created successfully\n");
	
	if(pthread_join(handle, (void **)&res)!=0){
		perror("pthread_join() error");
		exit(3);
	}
	
	printf("thread return %d\n", res);
	exit(EXIT_SUCCESS);
}

/*
void *func(void *arg){
	int *ret;
	printf("thread() argument with %s\n", (char *)arg);
	if((ret = (int *)malloc(20))==NULL){
		perror("malloc error");
		exit(2);
	}
	int i = atoi(arg);
	printf("i = %d\n", i);
	
	ret = &i;
	printf("ret = %p\n", ret);
	printf("i = %p\n", &i);
	printf("*ret = %d\n", *ret);
	pthread_exit(ret);
}

void main(int argc, char *argv[]){
	pthread_t handle;
	char line[256];
	int s, res;
	void *rt;
	
	if(pthread_create(&handle, NULL, func, argv[1]) != 0){
		perror("pthread_create() error");
		exit(1);
	}
	printf("Thread created successfully\n");
	
	if(pthread_join(handle, &rt)!=0){
		perror("pthread_join() error");
		exit(3);
	}
	
	printf("thread existed with %ls\n", (int *)rt);
	free(rt);
}*/
