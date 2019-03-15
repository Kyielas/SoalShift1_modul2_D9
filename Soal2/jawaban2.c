#include<stdio.h>
#include<sys/wait.h>
#include<pwd.h>
#include<grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/ivan/Sisop/Praktikum2")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    struct passwd *pwd;
	struct group *grp;
	struct stat fileinfo;

	pid_t child_id;
	int status;
	
	stat("/home/ivan/Sisop/Praktikum2/hatiku/elen.ku", &fileinfo);
	pwd=getpwuid(fileinfo.st_uid);
	grp=getgrgid(fileinfo.st_gid);
	
	chmod("/home/ivan/Sisop/Praktikum2/hatiku/elen.ku", 0777);
	
	if(strcmp(pwd->pw_name, "www-data")==0 && strcmp(grp->gr_name, "www-data")==0) {
			char *argv[3] = {"rm", "/home/ivan/Sisop/Praktikum2/hatiku/elen.ku", NULL};
	    	execv("/bin/rm", argv);
		
	}
    sleep(3);
  }
  exit(EXIT_SUCCESS);
}

