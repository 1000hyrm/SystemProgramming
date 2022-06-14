
//무한 loop를 돌면서 사용자가 키보드로 입력한 내용을 argv[1] 파일로 출력하고, argv[2] 시간이 지나면 종료되는 프로그램
/* ■ 사용자가 키보드로 입력한 모든 내용은 argv[1] 파일에 저장된다.
   ■ 프로그램이 수행되는 도중에 사용자가 control-C (SIGINT)를 입력하면, 종료되지 않고 이전의 동작을 계속 수행한다.
   ■ 프로그램이 수행되는 도중에 사용자가 control-\ (SIGQUIT)를 입력하면, 종료되지 않고 이전의 동작을 계속 수행한다.
   ■ argv[2]의 시간만큼 지나면, control-C와 control-\이 입력된 횟수를 stdout으로 출력하고 종료한다. */
/* 실행 예
[root@localhost]# ./a.out test 10
Hello World // 사용자가 입력
^C^C^C
^\^\^\^\^\
Time out!! // 10초 경과
SIGINT : 3
SIGQUIT : 5
[root@localhost]# cat test
Hello World
[root@localhost]#
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

int int_cnt = 0;
int quit_cnt = 0;

void signal_handler(int);
int main(int argc, char *argv[]){
	int i, j, fd;
	int size=0;
	char buf[512];

	close(1);
	if(open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644)<0){
		perror(argv[1]);
		exit(1);
	}
	signal(SIGALRM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	alarm(atoi(argv[2]));
	while(1){
		size = read(0, buf, 512);
		write(1, buf, size);
	}
}
void signal_handler(int sig){
	if(sig==SIGINT){
		int_cnt++;
	}
	else if(sig==SIGQUIT){
		quit_cnt++;
	}
	else if(sig==SIGALRM){
		close(1);
		dup(2);
		fprintf(stdout, "Time out!!\n");
		printf("SIGINT : %d\n", int_cnt);
		printf("SIGQUIT : %d\n", quit_cnt);
		exit(1);
	}
}
