#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <locale.h>

void weightedgraph(int** G, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) { 
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                G[i][j] = rand() % 10;
                G[j][i] = G[i][j]; 
            }
        }
    }
}

void floydWarshall(int** G, int n, int** dist) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else if (G[i][j] > 0) dist[i][j] = G[i][j];
            else dist[i][j] = INT_MAX;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void RadiusDiameter(int** dist, int n) {
    int* eccentricity = (int*)malloc(n * sizeof(int));
    int radius = INT_MAX;
    int diameter = 0;

    for (int i = 0; i < n; i++) {
        eccentricity[i] = 0;
        for (int j = 0; j < n; j++) {
            if (dist[i][j] > eccentricity[i] && dist[i][j] != INT_MAX) {
                eccentricity[i] = dist[i][j];
            }
        }
        if (eccentricity[i] < radius && eccentricity[i] > 0) {
            radius = eccentricity[i];
        }
        if (eccentricity[i] > diameter) {
            diameter = eccentricity[i];
        }
    }

    printf("\nЭксцентриситеты вершин:\n");
    for (int i = 0; i < n; i++) {
        printf("Вершина %d: %d\n", i, eccentricity[i]);
    }

    printf("\nРадиус графа: %d\n", radius);
    printf("Диаметр графа: %d\n", diameter);

    printf("\nЦентральные вершины: ");
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == radius) {
            printf("%d ", i);
        }
    }

    printf("\nПериферийные вершины: ");
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == diameter) {
            printf("%d ", i);
        }
    }
    printf("\n");

    free(eccentricity);
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    int n;

    printf("Введите количество вершин: ");
    scanf("%d", &n);

    int** G = (int**)malloc(n * sizeof(int*));
    int** dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        G[i] = (int*)malloc(n * sizeof(int));
        dist[i] = (int*)malloc(n * sizeof(int));
    }

    weightedgraph(G, n);

    printf("Матрица смежности неориентированного взвешенного графа:\n");  // Изменено название
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }

    floydWarshall(G, n, dist);

    printf("\nМатрица расстояний:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INT_MAX) printf(" INF");
            else printf("%4d", dist[i][j]);
        }
        printf("\n");
    }

    RadiusDiameter(dist, n);

    for (int i = 0; i < n; i++) {
        free(G[i]);
        free(dist[i]);
    }
    free(G);
    free(dist);

    return 0;
}