#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*  Single linked list implementation.
    Mouzakitis Nikolaos,2016.

    Functions: Add a node,inspect list's codes,
               delete a node,add a node at a
               given possition.
*/

struct nodes
{
    int code;
    struct nodes *next;
};


void insert_at(struct nodes *ihead,int pos)
{
    struct nodes *p,*lastlink,*newlink;
    int i;


    p = ihead;

    for (i = 1; i < pos; i++)
    {
        if(p->next == NULL)
        {
            printf("Error on possition entry.\n");
            return ;
        }
        p = p->next;

    }
    lastlink = p->next;
    newlink = (struct nodes *)malloc(sizeof(struct nodes));
    newlink->next = NULL;
    printf("Enter code:\n");
    scanf("%d",&(newlink->code));
    p->next = newlink;
    newlink->next = lastlink;

}


void print_all_nodes(struct nodes *head)
{
    struct nodes *p;
    p = head;

    while( (p->next) != NULL)
    {
        printf("code= %d\n",p->code);
        p = p->next;
    }
        printf("code= %d\n",p->code);
}

void delete_node(struct nodes *head) // deletes the last node of the list.
{                                    // algorithm used first loop to find where
    struct nodes *ptr;               //resides the last element and next loop
    int cnt=0,i;                     //to go in the node just before it.
    ptr = head;


    while( (ptr->next) != NULL)
    {
        ptr = ptr->next;
        cnt++;
    }
    ptr = head;
    for (i = 1; i < cnt; i++)
        ptr = ptr->next;

    ptr->next = NULL;

}

void add_node(struct nodes *head) //adds a node in the end of the list.
{


    struct nodes *ptr;
    ptr = head;


    while( (ptr->next) != NULL)
        ptr = ptr->next;

    ptr->next = (struct nodes *) malloc(sizeof(struct nodes)) ;
    ptr = ptr->next;
    printf("Enter code for new node:  ");
    scanf("%d",&(ptr->code));
    ptr->next = NULL;

}
int main(void)
{
    struct nodes first;
    int choice,possition;

    first.code = 1; // code is 1 for the head node.
    first.next = NULL;

    printf(".::MENU::.\n1.Add\n2.Show\n3.Delete\n4.Insert at possition\n5.exit\n");
    scanf("%d",&choice);

    while(choice != 5)
    {
        switch(choice){

            case 1: add_node(&first);
                    break;
            case 2: print_all_nodes(&first);
                    break;
            case 3: delete_node(&first);
                    break;
            case 4: printf("Enter possition:\n");
                    scanf("%d",&possition);
                    insert_at(&first,possition);
                    break;
            default:
                    printf("Unknown command\n");
        }
        printf(".::MENU::.\n1.Add\n2.Show\n3.Delete\n4.Insert at possition\n5.exit\n");
        scanf("%d",&choice);
    }

    return (0);
}
