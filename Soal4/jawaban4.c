#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <time.h>

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

  if ((chdir("/home/ivan/Documents/makanan/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
  int i=1;
  while(1) {
    time_t awal;
    struct stat fileinfo;
    stat("/home/ivan/Documents/makanan/makan_enak.txt", &fileinfo);
    awal = fileinfo.st_atime; //waktu akses
    time_t akhir = time(NULL); //waktu program berjalan
    if(difftime(akhir, awal)<=30) {	// kiri-kanan
      	char x[100];
      	sprintf(x, "%d", i);
      	char y[100]="/home/ivan/Documents/makanan/makan_sehat";
      	strcat(y, x);
      	strcat(y,".txt");
     
		FILE *fp = fopen(y, "w"); 
      	fclose(fp);
     	i++;
    }
    sleep(5);
  }
  exit(EXIT_SUCCESS);
}
