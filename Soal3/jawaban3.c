#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int main() {
  pid_t gen1;
  pid_t gen2;
  pid_t gen3;
  pid_t gen4;
  int status;
  int pipa[3];
  pipe(pipa);

  gen1 = fork();
  if (gen1 == 0) {
    char *unzip[5] = {"unzip", "/home/kyielas/modul2/campur2.zip","-d", "/home/kyielas/modul2/", NULL};
    execvp("unzip", unzip);
  } else {
	while((wait(&status)) > 0);
	printf("unzip ok\n");
	gen2 = fork();
	if(gen2 == 0){    	

	} else {

		gen3 = fork();
		if(gen3 == 0){
		printf("touch ok\n");
		char *touch[3] = {"touch", "/home/kyielas/modul2/daftar.txt", NULL};
		execvp("touch", touch);		
		
		} else {

			gen4 = fork();
			if(gen4 == 0){
			printf("ls ok\n");
			char *ls[3] = {"ls", "/home/kyielas/modul2/campur2/", NULL};
			dup2(pipa[1], 1);
			close(pipa[0]);
			execvp("ls", ls);
			
			} else {
			while ((wait(&status)) > 0);		
			printf("grep ok\n");
			char *grep[3] = {"grep", "[.]txt$", NULL};
			int isi = open("daftar.txt",O_WRONLY);
			dup2(pipa[0], 0);
			close(pipa[1]);
			dup2(isi, 1);
			execvp("grep", grep);
			close(pipa[0]);
			
			//FILE* pipe = fdopen (fd[0],"r");
			//FILE *isi = fopen("daftar.txt","w") 
			//char temp[200];
			//while(fgets(temp, sizeof(temp),rf)!=NULL){
			//	if(strstr(&temp[strlen(temp)-5], ".txt")!=NULL)
			//	fprintf(isi,"%s",temp);
			//}
			}
		}
	}

}
}






