#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include "ca.h"

// declare functions

void transferlive()
{

        //syslog(LOG_INFO,"Welcome Test");
        //varaible  used for piping
        int nbytes;
        //varaible used for piping
        char readbuffer[100];
        //creating a backup fork known as bpid
        int  bpid = fork();
        //creating the file descriptors
        int fd[2];
        //creating the pipe
        pipe(fd);


        //if this is true PID is a parent 
        if(bpid > 0)
        {
                //syslog(LOG_INFO,"test1");

                printf("Parent Process");

                close(fd[1]);
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                syslog(LOG_INFO, readbuffer);
                //kills parent make orphan
                //exit(EXIT_SUCCESS);
                //sends no output 

                //syslog(LOG_INFO,"test2");
        }
        else
        {

                //syslog(LOG_INFO,"test3");
                close(fd[0]);
                //lockfile operation
                int lock = lockfile();
                //used for the check system to copy files
                int  prechecker = live();

                //if  checker is  equal to anyting else that is not -1 it will allow the copying of the files to occur and passs a success message onto the user 
                if(prechecker == -1)
                {
                 syslog(LOG_INFO,"pre checker status : %d ",prechecker);
                 char message[] = "transfer failed";
                 write(fd[1],message,(strlen(message)+1));
                 unlockfile();
                }
                else
                {
                 syslog(LOG_INFO,"pre checker status : %d ",prechecker); 
                 char message[] = "transfer success";
                 write(fd[1],message,(strlen(message)+1));
                 unlockfile();
                }



}

}
int live()
{
        syslog(LOG_INFO, "Begining File Transfer check");
        //int value informs us if in fact transfer  was succesful or if it had failed
        int  prechecker = system("sudo cp -u /home/markoflanagan/CA1/intranet/intranet.txt /home/markoflanagan/CA1/live/live.txt");
        return prechecker;
        //syslog(LOG_INFO, "failed");
}
