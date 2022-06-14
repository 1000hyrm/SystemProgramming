/* “ls –l | grep datafile” 과 동일한 동작을 수행하는 lsGrep.c 프로그램

- 이 프로그램은 child process를 두 개 생성하며, 
- 첫 번째 child는 “ls –l”을 수행하고, 두 번째 child는 “grep datafile”을 수행한다.
- 수행되는 첫 번째 child의 standard output은 pipe로 redirect 된다. 
- 수행되는 두 번째 child의 standard input은 pipe로 redirect 된다.
- 따라서, 첫 번째 child가 출력한 내용이 파이프로 write 되며, 그 결과는 두 번째 child의 입력으로 들어가게 된다.
- ls 프로그램과 grep 프로그램은 /bin 디렉토리에 있다. (/bin/ls, /bin/grep) */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char text[80];

void read2line(char *input){
	while(1){
		read(0, input, 1);
		if(*input == '\n')
			break;
		else
			input++;
	}
}

int main(int argc, char *argv[]){
	int fd[2];
	
	if(pipe(fd)==-1){
		perror(argv[0]);
		exit(1);
	}
	
	if(fork()==0){
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		printf("display sorted\n");
		fflush(stdout);
		execl("/bin/ls", "ls", "-l", (char *)0);
		exit(127);
	}
	
	if(fork() == 0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		read2line(text);
		printf("\t heading : %s\n", text);
		fflush(stdout);
		execl("/bin/grep", "grep", "q.c", (char *)0);
		exit(127);
	}
	
	close(fd[0]);
	close(fd[1]);
	while(wait((int *)0) !=-1)
		;
	exit(0);
}
