#include <iostream>
#include <vector>
#include <queue>

// Функция bfs выполняет обход графа в ширину
void bfs(int start, const std::vector<std::vector<int>>& adjacency_list, std::vector<int>& visited) {
    std::queue<int> q;
    q.push(start);  // Добавляем начальную вершину в очередь
    visited[start] = 1;  // Помечаем начальную вершину как посещенную

    while (!q.empty()) {
        int current_vertex = q.front();  // Извлекаем текущую вершину из начала очереди
        q.pop();

        // Обрабатываем соседние вершины текущей вершины
        for (int neighbor : adjacency_list[current_vertex]) {
            if (!visited[neighbor]) {  // Если соседняя вершина еще не была посещена
                visited[neighbor] = 1;  // Помечаем соседнюю вершину как посещенную
                q.push(neighbor);  // Добавляем соседнюю вершину в очередь
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;  // Вводим количество вершин и ребер графа

    std::vector<std::vector<int>> adjacency_list(n);  // Создаем список смежности графа
    std::vector<int> visited(n, 0);  // Создаем массив посещенных вершин, изначально все вершины не посещены

    // Вводим ребра графа
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        adjacency_list[u].push_back(v);  // Добавляем смежные вершины в список смежности
        adjacency_list[v].push_back(u);
    }

    int start_vertex;
    std::cin >> start_vertex;  // Вводим начальную вершину

    bfs(start_vertex, adjacency_list, visited);  // Выполняем обход графа в ширину

    // Выводим список посещенных вершин
    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            std::cout << i << " ";
        }
    }

    return 0;
}
