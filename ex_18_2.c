#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>
int call_count = 0;
int pid;
void signalhandler(int);
void signalint(int);
void signalquit(int);

int main(){
   struct itimerval t_val;
   int status;
   if((pid = fork())== 0){
      printf("========\n");
      signal(SIGINT, signalhandler);
      signal(SIGQUIT, signalhandler);
      while(1){ 
         pause();
      }   
   }
   
   signal(SIGALRM, signalhandler);
   t_val.it_value.tv_sec = 2L;
   t_val.it_value.tv_usec = 5L;
   t_val.it_interval.tv_sec = 2L;
   t_val.it_interval.tv_usec = 5L;
   
   setitimer(ITIMER_REAL, &t_val, NULL);
   wait(&status);
   printf("status : 0x%x\n", status);
}

void signalhandler(int sig){
   if(sig == SIGALRM){
      call_count++;
      printf("callcount : %d\n", call_count);
      if(call_count > 3) kill(pid,SIGQUIT);
      kill(pid, SIGINT);
   }
   if(sig == SIGINT) {
      printf("interrupt signal\n");
   }
   if(sig == SIGQUIT) {
      exit(19);
   }
}
