#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
  key_t key;
  int shmid;
  char * data;
  char input[256];
  if ((key = ftok("shmeg.c", 'R')) == -1) {
        perror("ftok");
        exit(1);
  }
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);
  if(strlen(data)==0) {
    printf("Shared memory segment just created.\n");
  }
  else{
    printf("Segment:%s",data);
  }
  printf("Do you want to change the data in the segment?[y/n]");
  fgets(input,200,stdin);
  if(strcmp(input,"y\n") == 0){
    printf("Enter new data for segment:");
    fgets(input, 256, stdin);
    strcpy(data, input);
    printf("Segment is now:%s",data);
  }
  printf("Do you want to delete the segment?[y/n]");
  fgets(input, 256, stdin);
  if(strcmp(input, "y\n") == 0){
    shmctl(shmid, IPC_RMID, NULL);
  }
  else{
    shmdt(data);
  }
  return 0;
}
