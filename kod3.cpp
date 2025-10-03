#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void main(void)
{
    setlocale(LC_ALL, "rus");
    int n;

    printf("Введите размер массива: ");
    scanf("%d", &n);

    // Динамическое выделение памяти
    int* a = (int*)malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    printf("Введите %d элементов массива:\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    printf("Ваш массив: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    free(a); // Освобождение памяти
}
