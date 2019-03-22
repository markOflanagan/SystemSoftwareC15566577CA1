#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
//#include "ca.h"
#include <stdbool.h>


void logging()
{
	int fd[2];
	int pid;
	int nbytes;
	char readbuffer[100];

	pipe(fd);

   

    if(pid > 0) 
    {

        close(fd[1]);
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        syslog(LOG_INFO, readbuffer);
        exit (EXIT_SUCCESS);

    }
    else
    {
	close(fd[0]);




	int checker = system("sudo ausearch -f /home/markoflanagan/CA1 > /home/markoflanagan/CA1/logging.txt");


	if(checker == -1)
	{
	    char message[] = "Log file failed.";
            write(fd[1],message, (strlen(message)+1));
	}
	else
	{
	    char message[] = "Log file created.";
            write(fd[1],message, (strlen(message)+1));
	}




    }




}
