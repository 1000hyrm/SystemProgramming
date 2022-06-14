#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd[2], fd1;
	if(pipe(fd)==-1){
		perror("pipe error");
		exit(1);
	}
	if(fork()==0){
		close(1);
		if(fd1=open(argv[1], O_RDWR|O_CREAT|O_TRUNC)<0){
			perror(argv[1]);
			exit(2);
		}
		execv(argv[2], &argv[2]);
	}
}

