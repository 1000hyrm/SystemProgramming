//argv[1]으로 시간 (초 단위) 값이 입력되면, 해당 시간이 경과하면, 화면에 “Timeout”이라고 출력하고 종료하는 프로그램
/* - 단, 프로그램이 수행되는 도중에 사용자가 입력하는 control-C는 무시된다.
   - alarm(2) 을 사용하여 프로그래밍
   - 문자를 숫자로 변경하는 atoi 함수 이용 */
/*실행 예:
% a.out 5
// 5초가 경과
Timeout
% */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void fun(int num){
	printf("Timeout\n");
	exit(1);
}
int main(int argc, char *argv[]){
	signal(SIGALRM, fun);
	signal(SIGINT, SIG_IGN);
	alarm(atoi(argv[1]));
	
	while(1)
		;
}
