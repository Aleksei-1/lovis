#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>

int main() {
    int** G;
    int* loop;
    int* deg;
    int N, size;
    int i, j;
	setlocale(LC_ALL,"rus");
    
    srand(time(NULL));

    printf("Введите количество вершин графа: ");
    scanf("%d", &N);

    G = (int**)malloc(sizeof(int*) * N);
    for(i = 0; i < N; i++) {
        G[i] = (int*)malloc(N * sizeof(int));
    }
    loop = (int*)malloc(N * sizeof(int));
    deg = (int*)malloc(N * sizeof(int));

    for(i = 0; i < N; i++) {
        deg[i] = 0;
        loop[i] = 0;
    }

    for(i = 0; i < N; i++) {
        for(j = i; j < N; j++) {
            {
                int value = rand() % 2;
                G[i][j] = value;
                G[j][i] = value; 
            }
        }
    }

    printf("\nМатрица смежности графа G:\n    ");
    for(i = 0; i < N; i++) {
        printf("%3d", i);
    }
    printf("\n");
    
    for(i = 0; i < N; i++) {
        printf("%3d ", i);
        for(j = 0; j < N; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i < N; i++) {
        loop[i] = G[i][i]; 
        for(j = 0; j < N; j++) {
            if(i != j) {
                deg[i] += G[i][j]; 
            }
        }
       
        deg[i] += 2*loop[i];
    }

    size = 0;
    for(i = 0; i < N; i++) {
        for(j = i; j < N; j++) {
            if(G[i][j] == 1) {
                size++;
            }
        }
    }

    printf("\nРазмер графа G (количество ребер): %d\n", size);
    printf("Количество вершин: %d\n", N);

    printf("\nСтепени вершин:\n");
    for(i = 0; i < N; i++) {
        printf("Вершина %d: степень %d", i, deg[i]);
        if(loop[i] > 0) {
            printf(" (включая %d петлю)", loop[i]);
        }
        printf("\n");
    }

    printf("\nСпециальные вершины:\n");

    printf("Изолированные вершины (степень = 0): ");
    int found_isolated = 0;
    for(i = 0; i < N; i++) {
        if(deg[i] == 0) {
            if(found_isolated > 0) printf(", ");
            printf("%d", i);
            found_isolated++;
        }
    }
    if(found_isolated == 0) printf("отсутствуют");
    printf("\n");

    printf("Концевые вершины (степень = 1): ");
    int found_end = 0;
    for(i = 0; i < N; i++) {
        if(deg[i] == 1) {
            if(found_end > 0) printf(", ");
            printf("%d", i);
            found_end++;
        }
    }
    if(found_end == 0) printf("отсутствуют");
    printf("\n");

    printf("Доминирующие вершины (степень = %d): ", N-1);
    int found_dominating = 0;
    for(i = 0; i < N; i++) {
        if(deg[i] == N - 1) {
            if(found_dominating > 0) printf(", ");
            printf("%d", i);
            found_dominating++;
        }
    }
    if(found_dominating == 0) printf("отсутствуют");
    printf("\n");

    printf("\nДополнительная информация:\n");
    int total_degree = 0;
    for(i = 0; i < N; i++) {
        total_degree += deg[i];
    }
    printf("Сумма степеней всех вершин: %d\n", total_degree);
    printf("Проверка (должна быть равна 2 * размер графа): %d\n", 2 * size);

    for(i = 0; i < N; i++) {
        free(G[i]);
    }
    free(G);
    free(loop);
    free(deg);

	_getch();
    return 0;
}
