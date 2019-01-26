#include <unistd.h>
#include <stdio.h>
#include <wait.h>

pid_t exe_proc(char *path){

    char tmp[8];
    char *argv[3] = {path,tmp,(char *)0};


    pid_t cpid=fork();

    if( cpid == 0 ) {
          execv(path,argv);
    }
    printf("cpid=%d\n",cpid);
    return cpid;
          
}

int secondProcessPid;


int main() {

    int secondProcess_exitcode = 0;    
    int ret = 0;

    secondProcessPid = exe_proc("./second_process");
    printf("secondProcessPid = %d\n",secondProcessPid);    

    while(1)
    {
        ret = waitpid(secondProcessPid, &secondProcess_exitcode, WNOHANG);

        if( ret != 0)
            printf("Process exit!");

        printf("main_process is running!\n");
        sleep(3);

    }
   

   return 0;

}

