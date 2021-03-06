#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include "ca.h"
#include <stdbool.h>
//#include "backup.c"

//global variable seen below 
//int midnightcheck = 0;

bool  backCheck = false;

void server()
{

    //creating a child process
     int pid = fork();


    //if this is true PID is a parent 
     if(pid > 0)
     {

        syslog(LOG_INFO,"Parent Process Terminated");
	//kills parent make orphan
	exit(EXIT_SUCCESS);

     }
	// making sure it is a child process
     else if(pid==0)
     {
        


	//writing to file to inform the user what pid the child process is running
	//mimics running the ps aux command to obtain infor realting to this process
	//creating a new file  vairaible 
	FILE *pidfile;
	//opening the file for pid information in write mode
	pidfile = fopen("/home/markoflanagan/CA1/pidinfo.txt","w");
	//write message aka pid information to the file by obtaining the information of pid via getpid() function
	fprintf(pidfile, "The pid is %d", getpid());
	//closing the file
	fclose(pidfile);



	printf("Child Process");
	//used for logging purposes
	 openlog("slog", LOG_PID|LOG_CONS, LOG_USER);
	//log message 
         syslog(LOG_INFO, "Child Process Begins,Information Logged ");



       //begins a new process in a new session
	 if (setsid() < 0)
        {
            exit(EXIT_FAILURE);
        }
	//allows daemon to read/write with the permissions required
        umask(0);

	//ensures that any issues regarding mounted drives are handled 
        if (chdir("/") < 0)
        {
            exit(EXIT_FAILURE);
        }
	//closes all file descritpors 
        int x;
        for(x = sysconf(_SC_OPEN_MAX); x>=0; x--)
        {
            close(x);
        }




      }
}
//fucntion that will be used for locking the files that will be transfered and copied
int  lockfile()
{
        syslog(LOG_INFO,"File LockDown Begining");
	int Lcheck = system("chmod 444 /home/markoflanagan/SystemSoftwareC15566577CA1/CA1/intranet/intranet.txt");

	//lockdown variable used in backup.c program 	
	return  Lcheck;
}
//fucntion that will be used for unlocking the files mentioned above
void unlockfile()
{
	syslog(LOG_INFO,"File Unlocking");
        system("chmod 755 /home/markoflanagan/SystemSoftwareC15566577CA1/CA1/intranet/intranet.txt");
}
int main()
{


	//calling the above function
	server();
	while(1)
        	{
			syslog(LOG_INFO, "Daemon Server Begining");
			sleep(3);
			//crrating a time variable  to assign variable to systime
			time_t currentTime;
                	time(&currentTime);
			//converting time  varible to a tm  variable 
			struct tm *myTime = localtime(&currentTime);
			int midnightcheck =  myTime->tm_hour;
			//int midnightmin   =  myTime->tm_min;

			while(backCheck == false)
			{
				if(midnightcheck == 22) 
				{
					syslog(LOG_INFO, "CALLING BACKUP PROGRAM");
					backCheck = true;
                                        //logging();
//					backingUp(); 
					transferlive();

				}
			}




    		}
    		//log closing
    		closelog();
		return 0;

}

