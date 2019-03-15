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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
	struct dirent *entry;
	DIR *dir;	
	char file1[255];
	char file2[255];
	if(dir == NULL){
		printf("Tidak ada file");
		exit(1);
	}
	while(entry = readdir (dir)){
	strcpy(file1,entry->d_name);
	if(substrfinder(file1, ".png")){
		strncpy(file2,file1, strlen(file1)-4);
		strcat(file2,"_grey.png");
		rename(strcat(".",file1),strcat("/home/kyielas/modul2/gambar",file2));
		}
	}
	sleep(20);
  }
  exit(EXIT_SUCCESS);
}
