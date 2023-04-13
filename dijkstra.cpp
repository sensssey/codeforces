#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Функция dijkstra выполняет поиск кратчайших путей от начальной вершины до всех остальных вершин графа
void dijkstra(int start, const vector<vector<pair<int, int>>>& adjacency_list, vector<int>& dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0; // Расстояние от начальной вершины до самой себя равно 0
    pq.push({0, start}); // Добавляем начальную вершину в очередь с приоритетами

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        // Если текущее расстояние больше уже найденного, пропускаем итерацию
        if (current_distance > dist[current_vertex]) {
            continue;
        }

        // Обрабатываем соседние вершины текущей вершины
        for (const pair<int, int>& edge : adjacency_list[current_vertex]) {
            int neighbor = edge.first;
            int weight = edge.second;

            // Если найден более короткий путь, обновляем расстояние и добавляем вершину в очередь
            if (dist[current_vertex] + weight < dist[neighbor]) {
                dist[neighbor] = dist[current_vertex] + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adjacency_list(n);
    vector<int> dist(n, numeric_limits<int>::max());

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjacency_list[u].push_back({v, w});
        adjacency_list[v].push_back({u, w});
    }

    int start_vertex;
    cin >> start_vertex;

    dijkstra(start_vertex, adjacency_list, dist);

    for (int i = 0; i < n; i++) {
        cout << "Shortest path from " << start_vertex << " to " << i << " is: " << dist[i] << endl;
    }

    return 0;
}
