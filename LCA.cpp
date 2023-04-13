#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_LEVELS = 20; // Максимальное количество уровней предков (достаточно для дерева размером до 2^20)

vector<vector<int>> ancestor; // Массив предков
vector<int> depth; // Глубина каждой вершины в дереве

// Функция для инициализации массива предков и глубины вершин
void preprocess(const vector<vector<int>>& tree, int node, int parent) {
    ancestor[node][0] = parent;
    if (parent != -1) {
        depth[node] = depth[parent] + 1;
    }

    for (int child : tree[node]) {
        if (child != parent) {
            preprocess(tree, child, node);
        }
    }
}

// Функция для нахождения наименьшего общего предка двух вершин u и v
int lca(int u, int v) {
    // Если вершина u находится глубже в дереве, чем v, меняем их местами
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    // Поднимаем вершину u на один уровень с вершиной v с помощью двоичного подъема
    for (int i = MAX_LEVELS - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = ancestor[u][i];
        }
    }

    // Если вершины u и v уже совпадают, они являются наименьшим общим предком
    if (u == v) {
        return u;
    }

    // Ищем наименьшего общего предка, поднимаясь по дереву предков
    for (int i = MAX_LEVELS - 1; i >= 0; i--) {
        if (ancestor[u][i] != ancestor[v][i]) {
            u = ancestor[u][i];
            v = ancestor[v][i];
        }
    }

    return ancestor[u][0];
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    ancestor.assign(n, vector<int>(MAX_LEVELS, -1));
    depth.assign(n, 0);

    preprocess(tree, 0, -1);

    for (int j = 1; j < MAX_LEVELS; j++) {
        for (int i = 0; i < n; i++) {
            if (ancestor[i][j - 1] != -1) {
                ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
            }
        }
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }

    return 0;
}
