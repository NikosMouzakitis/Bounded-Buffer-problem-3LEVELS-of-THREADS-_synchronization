#include <stdio.h>
#define N 10

/*  Implementation of stack
    using an array.
    Mouzakitis Nikolaos,2016.
*/

int stack_pointer;
int stack[N];

void stack_push(int element)
{
        stack[stack_pointer++] = element;
}

int stack_pop(void)
{
    if(stack_pointer == 0)
        return (-1);
    else
        return (stack[--stack_pointer]);
}

void show_stack(void)
{
    int i;
    if(stack_pointer != 0 )

        for (i = 0; i < stack_pointer; i++)
            printf("Stack %d: %d\n",i,stack[i]);
    else
        printf("Empty stack\n");

}


int main (void)
{
    int element,choice,rv;

    printf(".::MENU::.\n1.Push\n2.Pop\n3.ShowStack\n4.Exit\n");
    scanf("%d",&choice);
    while(choice != 4)
    {
        switch(choice)
        {
            case 1:
                    if(stack_pointer == N )  //overflow checking.
                        printf("Unable to push.Stack is full.\n");
                    else
                    {
                        printf("Push\nEnter element to push:\n");
                        scanf("%d",&element);
                        stack_push(element);
                    }
                    break;

            case 2 :
                    printf("Pop\n");
                    rv = stack_pop();

                    if(rv != -1)
                        printf("Popped %d\n",rv);
                    else
                        printf("Cannot pop.Empty stack.\n");

                    break;

            case 3:
                    show_stack();
                    break;

            default:
                    printf("Unknown command\n");
        }
        printf(".::MENU::.\n1.Push\n2.Pop\n3.ShowStack\n4.Exit\n");
        scanf("%d",&choice);
    }


    printf("Stack implementation using a matrix.\nProgram completed.\n");
    return 0;
}
