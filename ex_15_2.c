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
