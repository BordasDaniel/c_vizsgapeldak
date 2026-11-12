#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    long* arr;
    short lenght;
    short values;
} IncomeStruct;


void RandomArrFiller(short arr[], const short lenght, const short min, const short max);

long IncomeCalc(short price, short quantity);

void ArrSorterMax(long arr[], const short lenght);

void ArrPrinter(long arr[], const short lenght);

short StringChecker(char string[]);

IncomeStruct StructCreator(long arr[], const short lenght, char filter[]);

void ArrExtender(long** arr, short* value);

short MatchIndexFinder(char filter[]);

void FilePrinter(long arr[], short lenght);


int main()
{
    const short arr_lenght = 5;
    const short min = 10;
    const short max = 50;
    
    short prices[] = {3500, 12000, 8500, 24000, 5400};
    short sold[arr_lenght];
    long income[arr_lenght];

    char userInput[20];

    srand(time(NULL));

    RandomArrFiller(sold, arr_lenght, min, max);

    for (int i = 0; i < arr_lenght; i++)
    {
        income[i] = IncomeCalc(prices[i], sold[i]);
    }


    ArrSorterMax(income, arr_lenght);
    ArrPrinter(income, arr_lenght);

    printf("Kerlek valassz: 'alacsony', 'kozepes', 'magas': ");
    if (fgets(userInput, sizeof(userInput), stdin) == NULL)
    {
        printf("Hibas ertek!\n");
        return 1;
    }

    userInput[strcspn(userInput, "\r\n")] = '\0';
    if (StringChecker(userInput) != 0)
    {
        printf("Hibas ertek!\n");
        return 1;
    }

    IncomeStruct structed = StructCreator(income, arr_lenght, userInput);
    ArrPrinter(structed.arr, structed.lenght);
    FilePrinter(structed.arr, structed.lenght);

    free(structed.arr);


    return 0;
}


void RandomArrFiller(short arr[], const short lenght, const short min, const short max)
{
    for (int i = 0; i < lenght; i++)
    {
        arr[i] = rand() % (max-min)+min;
    }
}

long IncomeCalc(short price, short quantity)
{
    return price * quantity;
}

void ArrSorterMax(long arr[], const short lenght)
{
    short tempIndex = 0;
    long tempValue = 0;
    short flagToSwap = 0;

    for (int i = 0; i < lenght - 1; i++)
    {
        for (int j = 1; j < lenght; j++)
        {
            if (arr[j] > arr[i])
            {
                tempIndex = j;
                tempValue = arr[j];
                flagToSwap = 1;
            }
        }

        if (flagToSwap)
        {
            arr[tempIndex] = arr[i];
            arr[i] = tempValue;
            tempIndex = 0;
            tempValue = 0;
            flagToSwap = 0;
        }

    }
}

void ArrPrinter(long arr[], const short lenght)
{
    for (int i = 0; i < lenght; i++)
    {
        printf("%ld ", arr[i]);
        printf("\n");
    }
}

short StringChecker(char string[])
{
    if(strcmp(string, "alacsony") == 0 || strcmp(string, "kozepes") == 0 || strcmp(string, "magas") == 0)
    {
        return 0;
    }
    return 1;
}

IncomeStruct StructCreator(long arr[], const short lenght, char filter[])
{
    short struct_lenght = 0;
    short struct_value = 2;
    long* struct_arr = malloc(struct_value * sizeof(long));
    short match = MatchIndexFinder(filter);

    for (int i = 0; i < lenght; i++)
    {
        switch (match)
        {
            case 0:
                if (!(arr[i] < 100000))
                {
                    continue;
                }

                if(struct_lenght == struct_value)
                {
                    ArrExtender(&struct_arr, &struct_value);
                }
                struct_arr[struct_lenght] = arr[i];
                struct_lenght++;
                break;
            
            case 1:
                if (!(arr[i] >= 100000 && arr[i] <= 500000))
                {
                    continue;
                }

                if(struct_lenght == struct_value)
                {
                    ArrExtender(&struct_arr, &struct_value);
                }
                struct_arr[struct_lenght] = arr[i];
                struct_lenght++;
                break;
            
            case 2:
                if (!(arr[i] > 500000))
                {
                    continue;
                }

                if(struct_lenght == struct_value)
                {
                    ArrExtender(&struct_arr, &struct_value);
                }
                struct_arr[struct_lenght] = arr[i];
                struct_lenght++;
                break;
        }
    }
    IncomeStruct incomeStruct;
    incomeStruct.arr = struct_arr;
    incomeStruct.lenght = struct_lenght;
    incomeStruct.values = struct_value;
    return incomeStruct;

}

short MatchIndexFinder(char filter[])
{
    if (strcmp(filter, "alacsony") == 0)
    {
        return 0;
    }
    else if (strcmp(filter, "kozepes") == 0)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

void ArrExtender(long** arr, short* value)
{
    *value *=2;
    long* temp = realloc(*arr, *value * sizeof(long));

    if(temp == NULL)
    {
        printf("Hiba helyfoglalas soran!\n");
        exit(1);
    }

    *arr = temp;

}

void FilePrinter(long arr[], short lenght)
{
    char fileName[] = "eredmenyek.txt";
    FILE* file = fopen(fileName, "w");

    if (file == NULL)
    {
        printf("Hiba az iras soran!\n");
        exit(1);
    }

    for (int i = 0; i < lenght; i++)
    {
        fprintf(file, "%d.: %ld\n", (i+1), arr[i]);
    }

    fclose(file);
}
