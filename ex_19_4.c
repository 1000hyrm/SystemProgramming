// thread 프로그램
/* - main 함수는 thread를 생성하여 실행하고, 생성한 thread가 종료할 때까지 기다리며, 생성한 thread가 종료하면 화면에 “OK”라고 출력하고 종료한다.
   - 생성된 thread는 화면에 “This is thread”라고 출력하고 1초 동안 sleep 한 후 종료한다 */

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
