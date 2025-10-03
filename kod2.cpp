#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void main(void)
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int n = 10;
    int a[10];

    printf("Массив случайных чисел: ");
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100; // Числа от 0 до 99
        printf("%d ", a[i]);
    }
    printf("\n");
}
