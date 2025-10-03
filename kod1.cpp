#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void main(void)
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL)); 

    int rows, cols;

    printf("Введите количество строк: ");
    scanf("%d", &rows);

    printf("Введите количество столбцов: ");
    scanf("%d", &cols);

    int** a = (int**)malloc(rows * sizeof(int*));

    if (a == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        a[i] = (int*)malloc(cols * sizeof(int));
        if (a[i] == NULL)
        {
            printf("Ошибка выделения памяти!\n");
           
            for (int j = 0; j < i; j++)
            {
                free(a[j]);
            }
            free(a);
            return;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            a[i][j] = rand() % 31 - 15; 
        }
    }

    printf("\nСгенерированный массив %dx%d:\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%4d ", a[i][j]); 
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++)
    {
        free(a[i]);
    }
    free(a);
}