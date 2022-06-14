/* Shell에서 “% a.out command option fileName” 실행하면, 
- command를 실행하고, 
- command가 stdout으로 출력하는 내용이 fileName에 저장되도록 하는 프로그램.
- 예를 들면, 다음과 같이 실행하면
% a.out /bin/date output
- /bin/date의 실행 결과가 stdout으로 출력되지 않고, “output”이라는 이름의 파일에 저장된다. 
- “option”은 없을 수 있다.
- “option”이 있는 경우, 맨 마지막 argument가 출력이 저장될 파일 이름이다.
- 예를들면, “% a.out /bin/ls -a -l output” 처럼 실행되면, “output”이 저장될 파일 이름이 된다.
- 이때, “output” 파일이 있으면, 파일에 있는 내용이 전부 삭제되도록 한다.
- 파일이 없는 경우 파일이 생성되며, 생성되는 파일의 mode는, 사용자는 read/write, 그룹/others 모두 read/execute만이 허용되도록 한다. (umask는 000이라고 가정한다.) */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 256
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[]){
	int i;
	char buf[MAX];
	int size=0;
	int s; //=char s;
	char line[256];
	char *path[MAX];
	char allpath[512];
	char option[MAX];
	int fd;
	
	for(i=0; i<argc; i++){
		printf("argv[%d]=[%s]\n", i, argv[i]);
		path[i] = argv[i];
		printf("path[%d]=[%s]\n", i, path[i]);
	}
	printf("i=%d\n", i);
	//strcat(allpath, "\"");
	strcpy(allpath, argv[1]);
	//strcat(allpath, "\"");
	printf("%s\n", allpath);
	
	for(int k=2; k<i-1; k++){
		strcpy(option, argv[k]);
	}
	printf("%s\n", option);
	
	printf("i=%d\n", i);
	//execl(allpath, "cmd", option, (char *)0);
	
	close(1);
	if(open(argv[i-1], O_WRONLY | O_CREAT | O_TRUNC, 0655)==-1){
		perror(argv[i-1]);
		exit(1);
	}
	close(2);
	if(dup(1) == -1){
		perror(argv[0]);
		exit(2);
	}
	printf("here\n");
	
	if(i < 4){
		execl(allpath, "cmd", (char *)0);
	}
	else
		execl(allpath, "cmd", option, (char *)0);
	//close(fd);
	exit(1);
}
