
//무한 루프를 돌면서, 사용자가 standard input(키보드)로부터 입력한 내용을 standard output(화면)에 출력하는 프로그램
/*수행 도중에 사용자가 CTRL+c를 눌러서 SIGINT 시그널을 발생 시키면, 화면에 "SIGINT"라고 출력하고 종료하지 않고 하던 일을 계속한다.
또한, 사용자가 CTRL+\를 눌려서 SIGQUIT 시그널을 발생시키면 화면에 "SIGQUIT"라고 출력하고 종료하도록 한다.*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void signalhandler(int);
int main(){
	int n;
	char buf[512];
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	while (1){
		n=read(0, buf, 512);
		write(1, buf, n);
	}
	exit(0);
}
void signalhandler(int sig){
	if(sig == SIGINT){
		printf("SIGINT\n");
	}
	else if(sig == SIGQUIT){
		printf("SIGQUIT\n");
		exit(1);
	}
}
