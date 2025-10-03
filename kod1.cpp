#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Функция для измерения времени перемножения матриц заданного размера
double measure_time(int n) {
    int i, j, r;

    // Выделяем память под матрицы динамически
    int** a = (int**)malloc(n * sizeof(int*));
    int** b = (int**)malloc(n * sizeof(int*));
    int** c = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        a[i] = (int*)malloc(n * sizeof(int));
        b[i] = (int*)malloc(n * sizeof(int));
        c[i] = (int*)malloc(n * sizeof(int));
    }

    // Заполнение матриц случайными числами
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = rand() % 100 + 1;
            b[i][j] = rand() % 100 + 1;
        }
    }

    // Замер времени начала вычислений
    clock_t start = clock();

    // Перемножение матриц
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = 0;
            for (r = 0; r < n; r++) {
                c[i][j] += a[i][r] * b[r][j];
            }
        }
    }

    // Замер времени окончания вычислений
    clock_t end = clock();

    // Освобождаем память
    for (i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main(void) {
    setlocale(LC_ALL, "Russian"); // Установка русской локали

    srand(time(NULL));

    // Увеличили максимальные размеры матриц для тестирования
    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("===================================================\n");
    printf("АНАЛИЗ ПРОИЗВОДИТЕЛЬНОСТИ ПЕРЕМНОЖЕНИЯ МАТРИЦ\n");
    printf("===================================================\n\n");

    printf("1. ПОРЯДОК СЛОЖНОСТИ ПРОГРАММЫ (О-СИМВОЛИКА)\n");
    printf("Алгоритм перемножения матриц имеет три вложенных цикла,\n");
    printf("каждый из которых выполняется n раз.\n");
    printf("Порядок сложности: O(n³)\n\n");

    printf("2. РЕЗУЛЬТАТЫ ИЗМЕРЕНИЯ ВРЕМЕНИ ВЫПОЛНЕНИЯ\n");
    printf("Размер матрицы | Время (сек) | Теоретическая оценка O(n³)\n");
    printf("---------------|-------------|---------------------------\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        double time_taken = measure_time(n);
        printf("%13d | %11.3f | O(%d³) = O(%'d)\n", n, time_taken, n, n * n * n);
    }
	getchar();
    return 0;
}
