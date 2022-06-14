
// Pipe를 생성하여, child는 argv[1] 문자열을 pipe로 write하고, parent는 pipe로 부터 read하여, 읽은 내용을 화면에 출력하는 프로그램

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
	int fd[2], size;
	char buf;
	if(pipe(fd)<0){
		perror("pipe");
		exit(1);
	}
	if(fork()==0){
		close(fd[1]);
		while(read(fd[0], &buf, 1)>0){
			write(STDOUT_FILENO, &buf, 1);
		}
		write(1, "\n", 1);
		close(fd[0]);
		exit(0);
	}
	else{
		close(fd[0]);
		write(fd[1], argv[1], strlen(argv[1]));
		close(fd[1]);
		wait(0);
		exit(-1);
	}
}
