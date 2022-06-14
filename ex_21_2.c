/* Child 프로세스를 생성하여 child 프로세스가 “/bin/date -u” 명령을 수행하도록 하는 프로그램.
이때, parent 프로세스는 child 프로세스가 종료할 때까지 기다린 후, child가 종료하면 child의 exit 값을 10진수로 출력하고 child pid를 10진수로 출력한다.*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	int status;
	int pid;
	if(fork()==0){
		execl("/bin/date", "cmd", "-u", (char *)0);
		exit(1);
	}
	wait(&status);
	printf("parent : child exit status=[%d]\n", status>>8);
}
