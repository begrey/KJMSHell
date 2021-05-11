#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
 
void signalHandler(int sig){
        if(sig==SIGINT){
                printf("signal SIGINT : %d\n", sig);
                //sleep(3000); //mac 에서는 sleep
                exit(0);
        }
        if(sig==SIGTSTP){
                printf("signal SIGTSTP : %d\n", sig);
				exit(0);
        }
        if(sig==SIGQUIT){
                printf("signal SIGQUIT : %d\n", sig);
				exit(0);
        }
}
int main(){
		char *str;

        signal(SIGINT, signalHandler);
        signal(SIGTSTP, signalHandler);
        signal(SIGQUIT, signalHandler);
        printf("input Ctrl+C or Ctrl+Z or Ctrl+\\ \n");
        while(1){
			fgets(str,sizeof(str),stdin);
			if (feof(stdin)){
				printf("Ctrl+D exit \n");
				exit(0);
			}
		}
}