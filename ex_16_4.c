
// child process는 argv[2] 실행 파일을 임의의 개수의 argument (argv[3], argv[4], ..., argv[n])로 실행하며, 그 결과는 pipe로 출력된다.
// parent는 pipe로부터 읽은 데이터를 argv[1] 파일에 저장한다.
/*실행 예
% a.out outfile /bin/ls -l
// “/bin/ls –l”을 실행하여, 그 결과를 outfile에 저장
% a.out outfile /bin/ls -l -a
// “/bin/ls –l -a”을 실행하여, 그 결과를 outfile에 저장
% a.out outfile /bin/ls -a -C -F
// “/bin/ls –a -C -F”을 실행하여, 그 결과를 outfile에 저장
% a.out outfile /bin/date -u
// “/bin/date –u”을 실행하여, 그 결과를 outfile에 저장*/

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

