#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

int main()//pid입력시 해당 프로그램 
{
int N;
pid_t pid;
scanf("%d", &N);
for(int i=0; i<N; i++){
scanf("%d",&pid);
kill(pid,SIGKILL);

}
    return 0;
}
