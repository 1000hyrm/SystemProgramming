/*  사용자가 n개의 argv를 입력하면, (n-1)개의 thread가 만들어진다.
- 예: “./a.out 1 5 9”를 수행하면 3개의 thread가 생성된다.
    각 스레드의 argument는 argv[i]가 되며,
- 1번 thread의 시작 argument는 “1” (문자열)
- 2번 thread의 시작 argument는 “5” (문자열)
- 3번 thread의 시작 argument는 “9” (문자열)
    각 thread는 시작하면 “sleep (1)”을 수행한 후, 수행 시작시 argument 값(int)의 제곱 값을 화면에 출력한다.
- 1번 thread는 1초 sleep 후에 1을 출력한 후 종료
- 2번 thread는 1초 sleep 후에 25를 출력한 후 종료
- 3번 thread는 1초 sleep 후에 81를 출력한 후 종료
    main thread는 생성한 모든 thread가 종료한 후 종료한다. */

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
	
