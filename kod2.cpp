#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

// Объявления функций сортировки
void shell(int *items, int count);
void qs(int *items, int left, int right);

// Функция сравнения для qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Функции заполнения массива
void fill_random(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;
}

void fill_ascending(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void fill_descending(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void fill_asc_desc(int *arr, int n) {
    int half = n / 2;
    for (int i = 0; i < half; i++) {
        arr[i] = i;                 // Первая половина возрастает
    }
    for (int i = half; i < n; i++) {
        arr[i] = n - (i - half);    // Вторая половина убывает
    }
}

// Универсальная функция измерения времени
double measure_time(void (*sort_func)(int*, int), int *arr, int n) {
    int *arr_copy = (int *)malloc(n * sizeof(int));
    memcpy(arr_copy, arr, n * sizeof(int));

    clock_t start = clock();
    sort_func(arr_copy, n);
    clock_t end = clock();

    free(arr_copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double measure_time_qs(void (*sort_func)(int*, int, int), int *arr, int n) {
    int *arr_copy = (int *)malloc(n * sizeof(int));
    memcpy(arr_copy, arr, n * sizeof(int));

    clock_t start = clock();
    sort_func(arr_copy, 0, n - 1);
    clock_t end = clock();

    free(arr_copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double measure_time_std_qsort(int *arr, int n) {
    int *arr_copy = (int *)malloc(n * sizeof(int));
    memcpy(arr_copy, arr, n * sizeof(int));

    clock_t start = clock();
    qsort(arr_copy, n, sizeof(int), compare);
    clock_t end = clock();

    free(arr_copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Реализации сортировок
void shell(int *items, int count) {
    int i, j, gap, k;
    int x, a[5] = {9, 5, 3, 2, 1};
    
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; j >= 0 && x < items[j]; j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int *items, int left, int right) {
    int i = left, j = right;
    int x = items[(left + right) / 2], y;
    
    do {
        while (items[i] < x && i < right) i++;
        while (x < items[j] && j > left) j--;
        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int main(void) {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    const int n = 10000;
    int *arr = (int *)malloc(n * sizeof(int));

    void (*fills[])(int*, int) = {fill_random, fill_ascending, fill_descending, fill_asc_desc};
    const char *types[] = {"Случайные", "Возрастание", "Убывание", "Возр.+Убыв."};
    
    printf("Тип данных     | Шелл (с) | QSort (с) | Std QSort (с)\n");
    printf("---------------|----------|-----------|-------------\n");

    for (int i = 0; i < 4; i++) {
        fills[i](arr, n);
        
        double t_shell = measure_time(shell, arr, n);
        double t_qs = measure_time_qs(qs, arr, n);
        double t_std = measure_time_std_qsort(arr, n);

        printf("%-14s | %8.4f | %9.4f | %12.4f\n", types[i], t_shell, t_qs, t_std);
    }
	getchar();
    free(arr);
    return 0;
}
