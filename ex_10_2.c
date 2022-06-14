#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void signalhandler(int);
int main(){
	int n;
	char buf[512];
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	while (1){
		n=read(0, buf, 512);
		write(1, buf, n);
	}
	exit(0);
}
void signalhandler(int sig){
	if(sig == SIGINT){
		printf("SIGINT\n");
	}
	else if(sig == SIGQUIT){
		printf("SIGQUIT\n");
		exit(1);
	}
}
