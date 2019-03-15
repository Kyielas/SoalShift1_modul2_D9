#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

bool substrfinder(const char *filename, const char *extension){
	size_t a= strlen(filename); 
	size_t b= strlen(extension);
	return a >= b && !strcmp(filename + a - b, extension);
}

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

  if ((chdir(".")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
	struct dirent *entry;
	DIR *dir = opendir(".") ;	
	char file1[255];
	char file2[255];
	if(dir == NULL){
		exit(1);
	}
	while((entry = readdir (dir))!=NULL){
	strcpy(file1,entry->d_name);
	if(strstr(&file1[strlen(file1)-4], ".png")){
		char file3[65] = {0};
		memset(file3, 0, sizeof(file3));
		memset(file2,0, sizeof(file2));
		strcpy(file3, "/home/kyielas/modul2/gambar/");
		strncpy(file2,file1, strlen(file1)-4);
		strcat(file2,"_grey.png");
		strcat(file3,file2);
		rename(file1,file3);
		}
	
	}
	sleep(10);
  }

  exit(EXIT_SUCCESS);
}
