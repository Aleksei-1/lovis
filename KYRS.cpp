#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// Константы для ограничений
const int MAX_VERTICES = 30;     // Максимальное количество вершин
const int MAX_EDGES = 200;       // Максимальное количество ребер

class DirectedGraph {
private:
    int vertices;
    vector<vector<int>> adjList;
    vector<vector<int>> reverseAdjList;

    void fillOrder(int v, vector<bool>& visited, stack<int>& orderStack);

public:
    DirectedGraph(int V);
    void addEdge(int v, int w);
    void generateRandomGraph(double edgeProbability);
    void printGraph();
    vector<vector<int>> findSCC();
    void printSCC(const vector<vector<int>>& scc);
};

// Конструктор
DirectedGraph::DirectedGraph(int V) : vertices(V) {
    adjList.resize(V);
    reverseAdjList.resize(V);
}

// Добавление ребра в граф
void DirectedGraph::addEdge(int v, int w) {
    adjList[v].push_back(w);
    reverseAdjList[w].push_back(v);
}

// Генерация случайного орграфа
void DirectedGraph::generateRandomGraph(double edgeProbability) {
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i != j && (rand() / (double)RAND_MAX) < edgeProbability) {
                addEdge(i, j);
            }
        }
    }
}

// Печать графа
void DirectedGraph::printGraph() {
    cout << "\nСписок смежности орграфа:\n";
    for (int i = 0; i < vertices; i++) {
        cout << "Вершина " << i << ":";
        for (int j : adjList[i]) {
            cout << " -> " << j;
        }
        cout << endl;
    }

    // Для больших графов не выводим матрицу
    if (vertices <= 15) {
        cout << "\nМатрица смежности:\n   ";
        for (int i = 0; i < vertices; i++) cout << setw(3) << i;
        cout << "\n";

        for (int i = 0; i < vertices; i++) {
            cout << setw(3) << i;
            for (int j = 0; j < vertices; j++) {
                bool hasEdge = false;
                for (int neighbor : adjList[i]) {
                    if (neighbor == j) {
                        hasEdge = true;
                        break;
                    }
                }
                cout << setw(3) << (hasEdge ? 1 : 0);
            }
            cout << endl;
        }
    }
    else {
        cout << "\n(Матрица смежности не выводится для графов с более чем 15 вершинами)\n";
    }
}

// Функция для заполнения порядка вершин
void DirectedGraph::fillOrder(int v, vector<bool>& visited, stack<int>& orderStack) {
    visited[v] = true;
    for (int neighbor : adjList[v]) {
        if (!visited[neighbor]) {
            fillOrder(neighbor, visited, orderStack);
        }
    }
    orderStack.push(v);
}

// Алгоритм Косарайю для нахождения сильно связных компонент
vector<vector<int>> DirectedGraph::findSCC() {
    stack<int> orderStack;
    vector<bool> visited(vertices, false);
    vector<vector<int>> scc;

    // Первый проход DFS
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            fillOrder(i, visited, orderStack);
        }
    }

    // Второй проход DFS на обратном графе
    fill(visited.begin(), visited.end(), false);

    while (!orderStack.empty()) {
        int v = orderStack.top();
        orderStack.pop();

        if (!visited[v]) {
            vector<int> component;
            stack<int> dfsStack;
            dfsStack.push(v);

            while (!dfsStack.empty()) {
                int current = dfsStack.top();
                dfsStack.pop();

                if (!visited[current]) {
                    visited[current] = true;
                    component.push_back(current);

                    for (int neighbor : reverseAdjList[current]) {
                        if (!visited[neighbor]) {
                            dfsStack.push(neighbor);
                        }
                    }
                }
            }
            scc.push_back(component);
        }
    }

    return scc;
}

// Печать сильно связных компонент
void DirectedGraph::printSCC(const vector<vector<int>>& scc) {
    cout << "\nСильно связные компоненты:\n";
    for (size_t i = 0; i < scc.size(); i++) {
        cout << "Компонента " << i + 1 << ": {";
        for (size_t j = 0; j < scc[i].size(); j++) {
            cout << scc[i][j];
            if (j != scc[i].size() - 1) cout << ", ";
        }
        cout << "}" << endl;
    }
    cout << "Всего компонент: " << scc.size() << endl;
}

// Демонстрационный пример
void demonstrateExample() {
    cout << "\n=== Пример работы алгоритма ===\n";

    DirectedGraph g(8);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.addEdge(6, 5);
    g.addEdge(6, 7);
    g.addEdge(7, 6);

    g.printGraph();
    vector<vector<int>> scc = g.findSCC();
    g.printSCC(scc);
}

// Функции для безопасного ввода
int inputInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число.\n";
        }
        else if (value < minVal || value > maxVal) {
            cout << "Ошибка! Число должно быть от " << minVal << " до " << maxVal << ".\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double inputDouble(const string& prompt, double minVal, double maxVal) {
    double value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число.\n";
        }
        else if (value < minVal || value > maxVal) {
            cout << "Ошибка! Число должно быть от " << minVal << " до " << maxVal << ".\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Создание случайного графа
DirectedGraph* createRandomGraph() {
    cout << "\nКоличество вершин (1-" << MAX_VERTICES << "): ";
    int vertices = inputInt("", 1, MAX_VERTICES);

    if (vertices > 20) {
        cout << "Внимание: для графов более 20 вершин вывод может быть большим.\n";
    }

    double probability = inputDouble("Вероятность ребра (0.0-1.0): ", 0.0, 1.0);

    DirectedGraph* g = new DirectedGraph(vertices);
    g->generateRandomGraph(probability);
    return g;
}

// Функция для ввода одного ребра
void inputEdge(int& v, int& w, int maxVertex, int edgeNum, int totalEdges) {
    while (true) {
        cout << "Ребро " << edgeNum << " из " << totalEdges << " (введите v w): ";
        if (!(cin >> v >> w)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите два числа через пробел.\n";
        }
        else if (v < 0 || v >= maxVertex || w < 0 || w >= maxVertex) {
            cout << "Ошибка! Вершины должны быть от 0 до " << maxVertex - 1 << ".\n";
        }
        else {
            break;
        }
    }
}

// Создание графа вручную
DirectedGraph* createManualGraph() {
    cout << "\nКоличество вершин (1-" << MAX_VERTICES << "): ";
    int vertices = inputInt("", 1, MAX_VERTICES);

    int maxEdges = vertices * (vertices - 1);
    if (maxEdges > MAX_EDGES) maxEdges = MAX_EDGES;

    cout << "Максимальное количество ребер: " << maxEdges << endl;
    int edges = inputInt("Количество ребер (0-" + to_string(maxEdges) + "): ", 0, maxEdges);

    DirectedGraph* g = new DirectedGraph(vertices);

    if (edges > 0) {
        cout << "\nВведите " << edges << " ребер (v w):\n";
        cout << "Пример: 0 1 (ребро из вершины 0 в вершину 1)\n";

        for (int i = 0; i < edges; i++) {
            int v, w;
            inputEdge(v, w, vertices, i + 1, edges);
            g->addEdge(v, w);
        }
    }

    return g;
}

// Главное меню
int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(nullptr)));

    DirectedGraph* graph = nullptr;
    int choice;

    do {
        cout << "\n=== Алгоритм Косарайю ===\n";
        cout << "1. Случайный граф\n";
        cout << "2. Ввести граф\n";
        cout << "3. Пример\n";
        cout << "4. Выход\n";
        cout << "Выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }

        switch (choice) {
        case 1:
            if (graph) delete graph;
            graph = createRandomGraph();
            if (graph) {
                graph->printGraph();
                vector<vector<int>> scc = graph->findSCC();
                graph->printSCC(scc);
            }
            break;

        case 2:
            if (graph) delete graph;
            graph = createManualGraph();
            if (graph) {
                graph->printGraph();
                vector<vector<int>> scc = graph->findSCC();
                graph->printSCC(scc);
            }
            break;

        case 3:
            demonstrateExample();
            break;

        case 4:
            cout << "Выход...\n";
            break;

        default:
            cout << "Неверный выбор!\n";
        }

        if (choice != 4) {
            cout << "\nНажмите Enter...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (choice != 4);

    if (graph) delete graph;
    return 0;
}