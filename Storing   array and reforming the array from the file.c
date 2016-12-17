#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 6

/*Implementation of storing a sparse matrix,
  as a line that has the row, column and value
  stored to it for each non-zero element
  and then regenerating the matrix from the text file.

  Mouzakitis Nikolaos,Crete 2016.

  */
main()
{
    FILE *fd;
    int array[N][M] = { {0,0,1,5,0,0},
                       {0, 2,0,1,0,0},
                       {0,0,0,0,0,0},
                       {1,0, 5,0,0,0},
                       {0,7,0,0,0,0}
    };
    int i,j,gen1,gen2,gen3,generated[N][M] ;

    int *p ;
    p = generated;

    for(i = 0; i < N*M;i++) // setting generated array to zero,so latter on the unsetted values will remain zero.
        *(p+i) = 0;

    fd = fopen("store.txt","w");
    if(fd == NULL)
    {
        printf("Error while opening file\n");
        exit(1);
    }

    for (i = 0; i < N; i++)
        for(j = 0; j < M; j++)
        {
            if(array[i][j] != 0)
            {

                fprintf(fd,"%d %d %d ",i,j,array[i][j]);

            }
        }

    printf("Store file generated succesfully.\n");

    if(fclose(fd) != 0)
        printf("Error closing the file.\n");


    fd = fopen("store.txt","r");

    if(fd == NULL)
    {
        printf("Error while opening file\n");
        exit(1);
    }

    printf("Generating array from file \"store.txt\"\n");


    while( fscanf(fd,"%d %d %d ",&gen1,&gen2,&gen3) != EOF)
        generated[gen1][gen2] = gen3;
    printf("Generation completed upon \"store.txt\" \n");

    printf("Printing array : \n");
    for(i = 0; i < N; i++)
    {
        for(j = 0;j < M; j++)
            printf("%d\t",generated[i][j]);
        putchar('\n');
    }

    if(fclose(fd) != 0)
        printf("Error closing the file.\n");
    return 0;
}
