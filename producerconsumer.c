#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define size 10
int breads=0;
pthread_mutex_t lock;
pthread_cond_t cond;
//producer
void * producer(void* (args)){
  while(1){
    pthread_mutex_lock(&lock);
      while(breads>=size){
        pthread_cond_wait(&cond,&lock);
      }
      breads++;
      printf("brad produced %d\n",breads);
      pthread_cond_broadcast(&cond);
      pthread_mutex_unlock(&lock);
      sleep(1);
  }
    return NULL;
}
//consumer
void * consumer(void* (args)){
  while(1){
    pthread_mutex_lock(&lock);
      while(breads<=0){
        pthread_cond_wait(&cond,&lock);
      }
      breads--;
      printf("brad consumed %d\n",breads);
      pthread_cond_broadcast(&cond);
      pthread_mutex_unlock(&lock);
      sleep(2);
  }
    return NULL;
}
//main
int main(){
    pthread_t pt,ct;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&pt,NULL,producer,NULL);
    pthread_create(&ct,NULL,consumer,NULL);
    pthread_join(pt,NULL);
    pthread_join(ct,NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}