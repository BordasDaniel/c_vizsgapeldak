#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef char* string;

typedef struct
{
    float lenght;
    float* array;
} SortedBmiValue;

void weightFiller(float weightArray[], const short n, const short min, const short max)
{
    for (int i = 0; i < n; i++) 
    {
        weightArray[i] = (float)(rand() % (max - min + 1) + min);
    }
}

float bmiCalculator(float weight, float height)
{
    return weight / pow(height, 2);
}

void arraySorterWithMax(float bmi[], short n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (bmi[j] > bmi[maxIndex])
            {
                maxIndex = j;
            }
        }
        if (maxIndex != i)
        {
            float temp = bmi[i];
            bmi[i] = bmi[maxIndex];
            bmi[maxIndex] = temp;
        }
    }
}

void arrayPrinter(const float array[], short n)
{
    for (int i = 0; i < n; i++) 
    {
        printf("%.2f ", array[i]);
    }
    printf("\n");
}

short stringChecker(const string stringToCheck)
{
    if (strcmp(stringToCheck, "sovany") == 0 || 
        strcmp(stringToCheck, "normalis") == 0 || 
        strcmp(stringToCheck, "elhizott") == 0) 
    {
        return 0; 
    }
    return 1;
}

void bmiArrayExtender(float** sortedBmi, short* sortedLenght, float value)
{
    (*sortedLenght)++;
    float* temp = realloc(*sortedBmi, (*sortedLenght) * sizeof(float));
    if (temp == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    *sortedBmi = temp;
    (*sortedBmi)[*sortedLenght - 1] = value;
}

SortedBmiValue bmiSorter(const float bmi[], short n, const string filter)
{
    short flag;

    if (strcmp(filter, "sovany") == 0) flag = 0;
    else if (strcmp(filter, "normalis") == 0) flag = 1;
    else flag = 2;

    short sortedLenght = 0;
    float* sortedBmi = NULL;

    for (int i = 0; i < n; i++)
    {
        switch (flag)
        {
            case 0:
                if (bmi[i] < 18.5) 
                {
                    bmiArrayExtender(&sortedBmi, &sortedLenght, bmi[i]);
                }
                break;

            case 1:
                if (bmi[i] >= 18.5 && bmi[i] <= 25) 
                {
                    bmiArrayExtender(&sortedBmi, &sortedLenght, bmi[i]);
                }
                break;

            case 2:
                if (bmi[i] > 25) 
                {
                    bmiArrayExtender(&sortedBmi, &sortedLenght, bmi[i]);
                }
                break;
        }
    }

    SortedBmiValue sortedBmiValue;
    sortedBmiValue.lenght = (float)sortedLenght;
    sortedBmiValue.array = sortedBmi;
    return sortedBmiValue;
}

void arrayToFile(const float bmi[], short n)
{
    FILE* file = fopen("bmi.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "BMI values:\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%.2f\n", bmi[i]);
    }
    fclose(file);
}

int main()
{
    const float height[] = {1.2f, 1.16f, 1.52f, 1.18f, 1.34f};
    const short min = 35;
    const short max = 50;
    const short n = 5;
    float weight[5];
    float bmi[5];
    
    short userInputLenght = 20;
    string userInput = malloc(userInputLenght * sizeof(char));
    if (userInput == NULL) 
    {
        return 1;
    }

    srand((unsigned int)time(NULL));
    
    weightFiller(weight, n, min, max);

    for (int i = 0; i < n; i++) 
    {
        bmi[i] = bmiCalculator(weight[i], height[i]); // Helyes sorrend: súly, magasság
    }
    
    arraySorterWithMax(bmi, n);
    printf("Minden BMI ertek csokkeno sorrendben:\n");
    arrayPrinter(bmi, n);

    // Ellenőrzött beolvasás
    printf("Please choose: 'sovany', 'normalis', 'elhizott': ");
    if (fgets(userInput, userInputLenght, stdin) != NULL)
    {
        userInput[strcspn(userInput, "\r\n")] = '\0';
    }

    if (stringChecker(userInput) != 0)
    {
        printf("Invalid value!\n");
        free(userInput);
        return 1;
    }

    SortedBmiValue result = bmiSorter(bmi, n, userInput);
    
    printf("Kivalogatott elemek:\n");
    arrayPrinter(result.array, (short)result.lenght);
    
    arrayToFile(result.array, (short)result.lenght);

    free(userInput);
    free(result.array);

    return 0;
}