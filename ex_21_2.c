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
