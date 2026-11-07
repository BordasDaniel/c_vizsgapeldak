#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void ArrayFiller(short randomArray[], short* n, short min, short max)
{
    for(int i = 0; i < *n ; i++)
    {
        randomArray[i] = (rand() % (max- min+1)+min);
    }
}

void ArrayReversePrinter(short randomArray[], short n)
{

    for(int i = n - 1; i >= 0; i--)
    {
        printf("%d ", randomArray[i]);
    }
}

void ArrayAvg(short randomArray[], short* n)
{
    int sum = 0;
    for(int i = 0; i < *n; i++)
    {
        sum += randomArray[i];
    }

    printf("\nAverage: %.2f\n", (float)sum / *n);
}

short Decider(short* lowend, short* highend)
{
    if(*lowend > *highend) return *lowend;
    else return *highend;
}


int main()
{
    short min = 0;
    short max = 50;
    short n = 10;
    short randomArray[n];
    short lowend, highend;

    srand(time(NULL));

    ArrayFiller(randomArray, &n, min, max);
    ArrayReversePrinter(randomArray, n);
    ArrayAvg(randomArray, &n);

    printf("Please insert the number from the lowend: ");
    if(scanf("%hd", &lowend) != 1 || lowend < 0 || lowend > 9)
    {
        printf("Invalid number!\n");
        return 1;
    }

    printf("Please insert the number from the highend: ");
    if(scanf("%hd", &highend) != 1 || highend < 0 || highend > 9 || lowend >= highend)
    {
        printf("Invalid number!\n");
        return 1;
    }

    printf("The higher number is: %d\n", Decider(&lowend, &highend));


    return 0;
}