/*  Child process는 시그널이 발생할 때까지 기다리며,
- SIGINT 시그널이 발생하면, 화면에 “interrupt signal”이라고 출력하고, 시그널이 발생할 때까지 다시 기다린다.
- SIGQUIT 시그널이 발생하면, “exit (19)”을 수행하고, 종료한다.
    Parent process는
- child에게 2.5초에 한 번씩 전체 3번의 SIGINT 시그널을 전송하며,
- child에게 3번의 SIGINT 시그널을 전송한 뒤, 2.5초 후에는 SIGQUIT 시그널을 전송한다.
- SIGQUIT 시그널을 전송한 후에는, child가 종료하기를 기다린 후, child의 exit 값을 16진수로 출력한다. */

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
