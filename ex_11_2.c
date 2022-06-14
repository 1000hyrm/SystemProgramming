#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void fun(int num){
	printf("Timeout\n");
	exit(1);
}
int main(int argc, char *argv[]){
	signal(SIGALRM, fun);
	signal(SIGINT, SIG_IGN);
	alarm(atoi(argv[1]));
	
	while(1)
		;
}
