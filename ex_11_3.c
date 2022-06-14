
//Parent 프로세스는 두 개의 child 프로세스와 pipe를 생성하여 동작하는 프로그램
/*- 첫 번째 child 프로세스는 argv[1] 프로그램을 실행하며, pipe의 file descriptor를 조작하여 argv[1]의 실행 결과가 stdout으로 출력되지 않고, pipe로 write 되도록 한다.
  - 두 번째 child 프로세스는 pipe의 file descriptor를 조작하여, stdin 파일의 입력이 pipe가 되도록 하며, stdin으로부터 데이터를 읽어 이를 stdout(화면)으로 출력되도록 한다.*/
/*실행 예:
  % a.out /bin/date
  // date의 실행결과
  % a.out /bin/ls
  // ls의 실행결과
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX 50
char text[80];

void read2line(char *input){
	while(1){
		read(0, input, 1);
		if(*input=='\n')
			break;
		else
			input++;
	}
}

int main(int argc, char *argv[]){
	int fd[2], pid=0, size=0, status=0;
	char buf[MAX];
	memset(buf, 0x00, MAX);
	
	if(pipe(fd)==-1){
		perror(argv[0]);
		exit(1);
	}
	
	if(fork()==0){
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		printf("%s", argv[1]);
		fflush(stdout);
		exit(3);
	}
	if(fork()==0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		
		size = read(0, buf, MAX);
		execlp(argv[1], buf, (char *)NULL);
		perror("execlp() :");
		exit(0);
	}

	/*if(fork()==0){
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		
		printf("displayed %s\n", argv[1]);
		fflush(stdout);
		
		//size = read(0, buf, MAX);
		//execlp(argv[1], buf, (char *)NULL);
		
		//execl(argv[1], "wow", (char *)0);
		//perror("execl () ");
		exit(3);
	}
	
	if(fork()==0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		//read2line(text);
		//printf("heading %s\n", text);
		execl(argv[1], "wow", (char *)0);
		fflush(stdout);
		exit(0);
	}*/
	
	close(fd[0]);
	close(fd[1]);
	while(wait(&status) != -1)
		;
	exit(0);
}
	
