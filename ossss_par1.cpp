#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
void *Reader(void *arg);
void *Writer(void *arg);
int rc=0;
sem_t i; 
sem_t j; 

int main(){
int a,b,n;
sem_init(&i, 0, 1);
sem_init(&j, 0, 1);
printf("\nEnter the no. of Readers: ");
scanf("%d",&a);
printf("\nEnter the no. of Writers: ");
scanf("%d",&b);
pthread_t read[5];
pthread_t write[5];
for (n = 0; n < a; n++){
pthread_create(&read[n], NULL, Reader, NULL);
}
for (n=0; n < b; n++){
pthread_create(&write[n], NULL, Writer, NULL);
}

for (n = 0; n < a; n++){
pthread_join(read[n], NULL);
}
for (n = 0; n < b; n++){
pthread_join(write[n], NULL);
}
return 0;
} 

void *Reader(void *arg){
sem_wait(&j);
rc++;

if (rc == 1){
sem_wait(&i);
printf("All Writers are waiting\n");
}
sem_post(&j);
printf("Reader is reading the Data \n");
printf("Reader is leaving\n");
sleep(1);
sem_wait(&j);
rc--;

if (rc == 0){
sem_post(&i);
}
sem_post(&j);
}

void *Writer(void *arg){
sem_wait(&i);

printf("Writer is writing the data\n");
sleep(1);
sem_post(&i);
}
  

