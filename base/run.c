#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void arrayFiller(short runArray[], short n, short min, short max)
{
    for(int i = 0; i < n; i++) 
    {
        runArray[i] = (rand() % (max - min + 1) + min);
    }
}

void arrayReversePrinter(short runArray[], short n)
{
    for(int i = n - 1; i >= 0; i--) 
    {
        printf("%hd ", runArray[i]);
    }
    printf("\n");
}

float kmAvg(short runArray[], short n)
{
    short sum = 0;
    for(int i = 0; i < n; i++) 
    {
        sum += runArray[i];
    }
    return (float)sum / n;
}

short Intervall(short runArray[], short n, short* lowend, short* highend)
{
    short count = 0;
    for(int i = 0; i < n; i++) 
    {
        if (runArray[i] >= *lowend && runArray[i] <= *highend) 
        {
            count++;
        }
    }
    return count;
}

int main()
{
    short min = 1;
    short max = 25;
    short n = 10;
    short runArray[10];
    short lowend, highend;
    
    srand(time(NULL));

    arrayFiller(runArray, n, min, max);
    
    printf("A tomb elemei forditott sorrendben: ");
    arrayReversePrinter(runArray, n);
    
    printf("A atlagosan lefutott km: %.2f km\n", kmAvg(runArray, n));

    printf("Add meg az alsó határt (1-25): ");
    if(scanf("%hd", &lowend) != 1 || lowend < min || lowend > max)
    {
        printf("Invalid number!\n");
        return 1;
    }

    printf("Add meg a felső határt (1-25): ");
    if(scanf("%hd", &highend) != 1 || highend > max || highend < min || highend < lowend)
    {
        printf("Invalid number!\n");
        return 1;
    }

    printf("Az intervallumba eso elemek szama: %hd\n", Intervall(runArray, n, &lowend, &highend));

    return 0;
}