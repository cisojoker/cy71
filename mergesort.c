#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4
#define SIZE 16
pthread_mutex_t mutex;
int array[SIZE] = {38, 27, 43, 3, 9, 82, 10, 29, 42, 2, 1, 8, 5, 6, 7, 4};
typedef struct {
    int left;
    int right;
} td;
//merge function
void merge(int left,int mid,int right){
int i,j,k;
int n1=mid-left+1;
int n2=right-mid;
int* l=(int *)malloc(n1*sizeof(int));
int* r=(int *)malloc(n2*sizeof(int));
for( i=0;i<n1;i++)
l[i]=array[left+i];
for( i=0;i<n2;i++)
r[i]=array[mid+i+1];
i=0;j=0;k=left;
 while(i<n1 && j<n2){
    if(l[i]>=r[j]){
       array[k++]=r[j++];
    }else{
        array[k++]=l[i++];
    }
 }
 while(i<n1){
     array[k++]=l[i++];
 }
 while(j<n2){
     array[k++]=r[j++];
 }free(l);free(r);
}
//second mergesort function 
void * mergesort(void* arg){
td * data=(td*)arg;
int l=data->left;
int r=data->right;
free (data);
if(l<r){
    int mid=(l+(r-l)/2);
    pthread_t lt,rt;
    td* ld=(td*)malloc(sizeof(td));
    td* rd=(td*)malloc(sizeof(td));

    ld->left=l;
    ld->right=mid;
    rd->left=mid+1;
    rd->right=r;

    pthread_create(&lt,NULL,mergesort,(void*)ld);
    pthread_create(&rt,NULL,mergesort,(void*)rd);

    pthread_join(lt,NULL);
    pthread_join(rt,NULL);

    merge(l,mid,r);
}

    return NULL;
}
// main function
int main(){
    pthread_t it;
      td* id=(td*)malloc(sizeof(td));
      	pthread_mutex_init(&mutex, NULL);
      id->left=0;id->right=SIZE-1;
      pthread_create(&it,NULL,mergesort,(void*)id);
pthread_join(it,NULL);
printf("sorted array:\n");
for(int i=0;i<SIZE;i++){
    printf("%d ",array[i]);
}
printf("\n");
	pthread_mutex_destroy(&mutex);
    return 0;
}