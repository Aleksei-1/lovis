#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char inf[256];
    int priority;
    struct node* next;
};

struct node* priority_head = NULL;
struct node* priority_last = NULL;
struct node* regular_head = NULL;
struct node* regular_last = NULL;

// Функция создания нового элемента
struct node* get_struct(int is_priority)
{
    struct node* p = NULL;
    char s[256];
    int priority = 0;

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf("%255s", s); // Безопасный ввод
    getchar(); // Очистка буфера

    if (is_priority)
    {
        printf("Введите приоритет объекта: ");
        scanf("%d", &priority);
        getchar(); // Очистка буфера

        if (priority < 1)
        {
            printf("Приоритет должен быть положительным числом!\n");
            free(p);
            return NULL;
        }
    }

    if (strlen(s) == 0)
    {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy(p->inf, s);
    p->priority = priority;
    p->next = NULL;

    return p;
}

// Функция добавления элемента в приоритетную очередь
void priority_enqueue(void)
{
    struct node* p = NULL;
    struct node* current = NULL;
    struct node* prev = NULL;

    p = get_struct(1);
    if (p == NULL)
    {
        return;
    }

    if (priority_head == NULL || p->priority < priority_head->priority)
    {
        p->next = priority_head;
        priority_head = p;
        if (p->next == NULL) {
            priority_last = p;
        }
        return;
    }

    // Поиск места для вставки (чем меньше число - тем выше приоритет)
    current = priority_head;
    while (current != NULL && current->priority <= p->priority)
    {
        prev = current;
        current = current->next;
    }

    // Вставка элемента
    prev->next = p;
    p->next = current;

    // Если элемент стал последним
    if (current == NULL)
    {
        priority_last = p;
    }
}

// Функция добавления элемента в обычную очередь (в конец)
void enqueue(void)
{
    struct node* p = NULL;
    p = get_struct(0);
    if (p == NULL)
    {
        return;
    }

    if (regular_head == NULL)
    {
        regular_head = p;
        regular_last = p;
    }
    else
    {
        regular_last->next = p;
        regular_last = p;
    }
}

// Функция просмотра очередей
void review(void)
{
    struct node* struc = priority_head;

    printf("\n    ПРИОРИТЕТНАЯ ОЧЕРЕДЬ    \n");
    if (priority_head == NULL)
    {
        printf("Очередь пуста\n");
    }
    else
    {
        while (struc)
        {
            printf("Имя: %s, Приоритет: %d\n", struc->inf, struc->priority);
            struc = struc->next;
        }
    }

    struc = regular_head;
    printf("\n    ОБЫЧНАЯ ОЧЕРЕДЬ    \n");
    if (regular_head == NULL)
    {
        printf("Очередь пуста\n");
    }
    else
    {
        while (struc)
        {
            printf("Имя: %s\n", struc->inf);
            struc = struc->next;
        }
    }
}

// Функция извлечения элемента из приоритетной очереди
struct node* dequeue_priority(void)
{
    struct node* temp = priority_head;
    if (priority_head == NULL)
    {
        printf("Приоритетная очередь пуста\n");
        return NULL;
    }

    priority_head = priority_head->next;
    if (priority_head == NULL)
    {
        priority_last = NULL;
    }
    temp->next = NULL;
    return temp;
}

// Функция извлечения элемента из обычной очереди
struct node* dequeue_regular(void)
{
    struct node* temp = regular_head;
    if (regular_head == NULL)
    {
        printf("Обычная очередь пуста\n");
        return NULL;
    }

    regular_head = regular_head->next;
    if (regular_head == NULL)
    {
        regular_last = NULL;
    }
    temp->next = NULL;
    return temp;
}

// Функция поиска элемента по имени в приоритетной очереди
struct node* find_priority(char* name)
{
    struct node* struc = priority_head;
    if (priority_head == NULL)
    {
        printf("Приоритетная очередь пуста\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            return struc;
        }
        struc = struc->next;
    }

    printf("Элемент не найден в приоритетной очереди\n");
    return NULL;
}

// Функция поиска элемента по имени в обычной очереди
struct node* find_regular(char* name)
{
    struct node* struc = regular_head;
    if (regular_head == NULL)
    {
        printf("Обычная очередь пуста\n");
        return NULL;
    }

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            return struc;
        }
        struc = struc->next;
    }

    printf("Элемент не найден в обычной очереди\n");
    return NULL;
}

// Главная функция
int main()
{
    setlocale(LC_ALL, "rus");
    int choice;
    char name[256];
    struct node* temp;

    while (1)
    {
        printf("\n1. Добавить элемент в приоритетную очередь\n");
        printf("2. Добавить элемент в обычную очередь\n");
        printf("3. Просмотреть очереди\n");
        printf("4. Найти элемент\n");
        printf("5. Извлечь элемент из очереди\n");
        printf("6. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar(); // Очистка буфера

        switch (choice)
        {
        case 1:
            priority_enqueue();
            break;
        case 2:
            enqueue();
            break;
        case 3:
            review();
            break;
        case 4:
            printf("Введите имя для поиска: ");
            scanf("%255s", name);

            printf("\n--- Поиск в приоритетной очереди ---\n");
            temp = find_priority(name);
            if (temp != NULL)
            {
                printf("Найден: %s с приоритетом %d\n", temp->inf, temp->priority);
            }

            printf("\n--- Поиск в обычной очереди ---\n");
            temp = find_regular(name);
            if (temp != NULL)
            {
                printf("Найден: %s\n", temp->inf);
            }
            break;
        case 5:
            printf("Извлечь из:\n");
            printf("1. Приоритетной очереди\n");
            printf("2. Обычной очереди\n");
            printf("Выберите очередь: ");
            scanf("%d", &choice);
            getchar();

            if (choice == 1)
            {
                temp = dequeue_priority();
                if (temp != NULL)
                {
                    printf("Извлечен элемент из приоритетной очереди: %s (приоритет: %d)\n", temp->inf, temp->priority);
                    free(temp);
                }
            }
            else if (choice == 2)
            {
                temp = dequeue_regular();
                if (temp != NULL)
                {
                    printf("Извлечен элемент из обычной очереди: %s\n", temp->inf);
                    free(temp);
                }
            }
            else
            {
                printf("Неверный выбор\n");
            }
            break;
        case 6:
            // Очистка памяти перед выходом
            while (priority_head != NULL)
            {
                temp = priority_head;
                priority_head = priority_head->next;
                free(temp);
            }
            while (regular_head != NULL)
            {
                temp = regular_head;
                regular_head = regular_head->next;
                free(temp);
            }
            exit(0);
        default:
            printf("Неверный выбор\n");
        }
    }
    return 0;
}