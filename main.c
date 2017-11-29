#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>

#define B1_SIZE 10			/* bounded buffer between level 1 and 2 . */
#define B2_SIZE 5			/* boudned buffer between level 2 and 3 . */
#define L1_THREADS 3		/* threads at level 1 . */
#define L2_THREADS 2		/* threads at level 2 . */
#define L3_THREADS 2		/* threads at level 3 . */

#define SHARED 0   			/* Linux shared between theads but not processes.*/
//#define SHARED 1 			/* Solaris shared between processes */


long produced1;				/* data produced by level1 producers	*/
long consumed2;				/* data consumed by level2 consumers	*/
long produced2;				/* data produced by level2 producers	*/
long consumed3;				/* data consumed by level3 consumers	*/

sem_t l1_empty,l1_occupied,l2_empty,l2_occupied;

/*C-consume	P-produce		*/
pthread_mutex_t PMTX_BUF1 = PTHREAD_MUTEX_INITIALIZER;	
pthread_mutex_t CMTX_BUF1 = PTHREAD_MUTEX_INITIALIZER;	
pthread_mutex_t PMTX_BUF2 = PTHREAD_MUTEX_INITIALIZER;	
pthread_mutex_t CMTX_BUF2 = PTHREAD_MUTEX_INITIALIZER;

/* Buffers implemented as a single circular linked lists */
struct buffer {
	int val;
	struct buffer *next;
}*buf1,*buf2,*front_b1,*back_b1,*front_b2,*back_b2;	

void * l1_producer(void * arg)
{
	int i = (int *)arg;
	
	printf("L1 prod[%d] starts producing\n",i);

	while(1)
	{
		sem_wait(&l1_empty);			//semWAIT
		pthread_mutex_lock(&PMTX_BUF1);	// MUTUAL EXCLUSION
		
		front_b1->val = produced1;
		produced1++;
		printf("L1:Producer[%d]: produced:%d \n",i,front_b1->val);
		fflush(stdout);
		front_b1 = front_b1->next;		
		
		pthread_mutex_unlock(&PMTX_BUF1);	//MUTUAL EXCLUSION		
		sem_post(&l1_occupied);			    //semPOST

		if(lrand48()%2 == 1)
			pthread_yield();
	}
}

void * l2_prod_con(void * arg)
{
	int i = (int *) arg;
	printf("L2:Thread[%d] starts producting/consuming\n",i);

	while(1){
		sem_wait(&l1_occupied);
		pthread_mutex_lock(&CMTX_BUF1);
		pthread_mutex_lock(&PMTX_BUF2);
		
		printf("                     L2:Thread[%d]: consumed:%d \n",i,back_b1->val);
		fflush(stdout);
		consumed2 = back_b1->val;	
		back_b1 = back_b1->next;	
		produced2 = consumed2 % 10 ;	/* simple calculation before sended to buffer2 */
		
		sem_wait(&l2_empty);		

		front_b2->val = produced2;
		printf("				L2:Thread[%d]: produced:%d \n",i,front_b2->val);
		front_b2 = front_b2->next;
		
		sem_post(&l2_occupied);
		
		pthread_mutex_unlock(&PMTX_BUF2);
		pthread_mutex_unlock(&CMTX_BUF1);
		sem_post(&l1_empty);
		
		if(lrand48()%2 == 1)
			pthread_yield();
	}
}

void * l3_consumer(void *arg)
{
	int i = (int *)arg;
	
	printf("L3 cons[%d] starts consuming\n",i);

	while(1)
	{
		sem_wait(&l2_occupied);		
		pthread_mutex_lock(&CMTX_BUF2);
		
		consumed3 = back_b2->val;
		
		printf("						L3:Consumer[%d]: consumed:%d \n",i,consumed3);
		fflush(stdout);
		back_b2 = back_b2->next;		
		
		pthread_mutex_unlock(&CMTX_BUF2);			
		sem_post(&l2_empty);			

		if(lrand48()%2 == 1)
			pthread_yield();
	}
}

struct buffer * create_buffer(struct buffer *arg,int len)
{
	int i;
	struct buffer *head = arg;
	struct buffer *p,*tmp;
	
	head = (struct buffer *)malloc(sizeof(struct buffer));
	
	if(head == NULL){
		printf("malloc\n");
		exit(-1);
	}

	tmp = head;
	for( i = 0; i < len-1; i++){
		p = (struct buffer *)malloc(sizeof(struct buffer));
		
		if(p == NULL){
			printf("malloc\n");
			exit(-1);
		}
		tmp->next = p;
		tmp = p;
	}
	tmp->next = head;

	return head;
}

int main(int argc,char *argv[])
{	
	pthread_t level1[L1_THREADS],level2[L2_THREADS],level3[L3_THREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
	int i;

	/*creating buffers of required sizes.*/
	buf1 = create_buffer(buf1,B1_SIZE);
	buf2 = create_buffer(buf2,B2_SIZE);
	
	sem_init(&l1_empty,SHARED,B1_SIZE);
	sem_init(&l1_occupied,SHARED,0);
	sem_init(&l2_empty,SHARED,B2_SIZE);
	sem_init(&l2_occupied,SHARED,0);

	front_b1 = back_b1 = buf1;
	front_b2 = back_b2 = buf2;

	for( i = 0; i < L1_THREADS; i++)
		pthread_create(&level1[i],&attr,l1_producer,(void *)i);
	for( i = 0; i < L2_THREADS; i++)
		pthread_create(&level2[i],&attr,l2_prod_con,(void *)i);
	for( i = 0; i < L3_THREADS; i++)
		pthread_create(&level3[i],&attr,l3_consumer,(void *)i);
	for( i = 0; i < L1_THREADS; i++)
		pthread_join(level1[i],NULL);
	for( i = 0; i < L2_THREADS; i++)
		pthread_join(level2[i],NULL);
	for( i = 0; i < L3_THREADS; i++)
		pthread_join(level3[i],NULL);

	sem_destroy(&l2_empty);
	sem_destroy(&l2_occupied);
	sem_destroy(&l1_empty);
	sem_destroy(&l1_occupied);

	sem_close(&l2_empty);
	sem_close(&l2_occupied);
	sem_close(&l1_empty);
	sem_close(&l1_occupied);

	free(buf1);
	free(buf2);
	return (0);
}
