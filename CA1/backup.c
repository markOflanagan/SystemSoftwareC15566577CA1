#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include "ca.h"

// declare functions

void backingUp()
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
		nbytes = read(fd[0],readbuffer,sizeof(readbuffer));
		syslog(LOG_INFO, readbuffer);
		//kills parent make orphan
        	exit(EXIT_SUCCESS);
		//sends no output 

		//syslog(LOG_INFO,"test2");
    	}
	else
	{

		//syslog(LOG_INFO,"test3");
		close(fd[0]);
		//lockfile operation
		int lock = lockfile();

		if(lock == -1)
		{
			unlockfile();
			//syslog(LOG_INFO, "locking file has failed");
			char message[] = "backup has failed";
                        write(fd[1],message,(strlen(message)+1));

		}
		else
		{
			
			int backcheckerr = fbackup();
			syslog(LOG_INFO, "backchekerr status %d ", backcheckerr);
			//if the backcher returns with a -1 it will notify the user that the backup has failed.
			if(backcheckerr == -1)
			{
//				syslog(LOG_INFO, "backup has failed");
				char message[] = "backup has failed";
                		write(fd[1],message,(strlen(message)+1));
			}
			else
			{

//				syslog(LOG_INFO, "backup passed!!!");
				char message[] = "backup passed!!!";
                		write(fd[1],message,(strlen(message)+1));

			}
		}
	}
}

int fbackup()
{
	syslog(LOG_INFO, "Beginning Backup checker");
	//int value informs us if in fact backup was succesful or if it had failed
	int  backchecker = system("sudo cp -u /home/markoflanagan/SystemSoftwareC15566577CA1/CA1/intranet/intranet.txt /home/markoflanagan/SystemSoftwareC15566577CA1/CA1/backup/backup.txt");
	return backchecker;
	//syslog(LOG_INFO, "failed");
}


