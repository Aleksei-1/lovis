#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

void main(void)
{
    setlocale(LC_ALL, "rus");
    int rows = 3, cols = 4;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // Сумма по строкам
    printf("Сумма по строкам:\n");
    for (int i = 0; i < rows; i++)
    {
        int row_sum = 0;
        for (int j = 0; j < cols; j++)
        {
            row_sum += matrix[i][j];
        }
        printf("Строка %d: %d\n", i + 1, row_sum);
    }

    // Сумма по столбцам
    printf("\nСумма по столбцам:\n");
    for (int j = 0; j < cols; j++)
    {
        int col_sum = 0;
        for (int i = 0; i < rows; i++)
        {
            col_sum += matrix[i][j];
        }
        printf("Столбец %d: %d\n", j + 1, col_sum);
    }
}
