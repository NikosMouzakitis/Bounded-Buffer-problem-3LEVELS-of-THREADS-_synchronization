#include <stdio.h>
#define N 10
/*  Queue implementation
    using an array.
    Mouzakitis Nikolaos,2016.
    qoper_proccess() makes sure that the queue is working,shifting the queue backwards on the matrix so new elements can be inserted.
    ip: insert pointer.
    rp: remove pointer.
*/
int queue[N];
int ip,rp;

void show_queue(void);
void qinsert(int element);
int qremove(void);
void qoper_proccess(void);
int main(void)
{

    int choice,rv,element;

    printf(".::MENU::.\n1.Insert\n2.Remove\n3.InspectQueue\n4.Exit\n");
    scanf("%d",&choice);
    while(choice != 4)
    {
        switch(choice) {
            case 1:
                    if( ip == N)
                        printf("Full queue.Unable to insert.\n");
                    else
                    {
                        printf("Enter element to insert.\n");
                        scanf("%d",&element);
                        qinsert(element);
                    }

                    break;

            case 2:

                    rv = qremove();
                    if(rv != -1)
                        printf("Removed %d\n",rv);
                    else
                        ;

                    break;

            case 3:
                    show_queue();
                    break;

            default:
                    printf("Unknown command\n");
                    }

        qoper_proccess();

        printf(".::MENU::.\n1.Insert\n2.Remove\n3.InspectQueue\n4.Exit\n");
        scanf("%d",&choice);
    }

    return 0;
}

void qinsert(int element)
{
    queue[ip++] = element;
}

int qremove(void)
{
    if(ip == rp)
    {
        printf("Empty queue\n");
        return -1;
    }
    else
        return (queue[rp++]);
}

void show_queue(void)
{
    int i;
    for ( i = rp; i < ip; i++)
        printf("queue: %d\n",queue[i]);

}
void qoper_proccess(void)
{
    int i;

    if(rp == ip)
        rp=ip=0;

    if( (ip == N) && (rp < N) && (rp > 0) )
    {
        for(i = 0; i < N - rp; i ++)
            queue[i] = queue[rp + i];

        ip = N - rp;
        rp = 0;

    }
}
