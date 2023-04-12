#include <bits/stdc++.h>
using namespace std;

vector<long long> segtree; // дерево отрезков
vector<long long> v; // исходный массив

// Функция для построения дерева отрезков
void build_segtree(long long node, long long start, long long end) {
    if (start == end) {
        // Если участок массива, соответствующий текущему узлу, содержит только один элемент,
        // присваиваем значение этого элемента узлу
        segtree[node] = v[start];
    } else {
        // Иначе рекурсивно строим дерево отрезков для левой половины участка массива, начиная с узла 2*node+1,
        // и для правой половины участка массива, начиная с узла 2*node+2
        long long mid = (start + end) / 2;
        build_segtree(2*node+1, start, mid);
        build_segtree(2*node+2, mid+1, end);
        // Затем вычисляем сумму элементов на участке, соответствующем текущему узлу, как сумму значений узлов дочерних узлов
        segtree[node] = segtree[2*node+1] + segtree[2*node+2];
    }
}

// Функция для обновления значения в дереве отрезков
void update_segtree(long long node, long long start, long long end, long long idx, long long val) {
    if (start == end) {
        // Если участок массива, соответствующий текущему узлу, содержит только один элемент,
        // присваиваем ему новое значение
        v[idx] = val;
        segtree[node] = val;
    } else {
        // Иначе рекурсивно обновляем значение в соответствующем дочернем узле
        long long mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update_segtree(2*node+1, start, mid, idx, val);
        } else {
            update_segtree(2*node+2, mid+1, end, idx, val);
        }
        // Затем вычисляем сумму значений узлов дочерних узлов и присваиваем эту сумму текущему узлу
        segtree[node] = segtree[2*node+1] + segtree[2*node+2];
    }
}

// Функция для выполнения запроса на сумму элементов на участке массива
long long query_segtree(long long node, long long start, long long end, long long l, long long r) {
    if (r < start || end < l) {
        // Если участок, соответствующий текущему узлу, не пересекается с заданным участком массива, в
        // значит, этот узел не вносит вклад в ответ, возвращаем ноль
        return 0;
    }
    if (l <= start && end <= r) {
        // Если участок, соответствующий текущему узлу, полностью содержится в заданном участке массива,
        // возвращаем значение узла
        return segtree[node];
    }
    // Иначе рекурсивно вычисляем суммы значений узлов дочерних узлов
    long long mid = (start + end) / 2;
    long long sum_left = query_segtree(2 * node + 1, start, mid, l, r);
    long long sum_right = query_segtree(2 * node + 2, mid + 1, end, l, r);
    // И возвращаем сумму значений узлов дочерних узлов
    return sum_left + sum_right;
}

signed main(){
    long long n; cin >> n;
    v.resize(n);
    for (long long i = 0; i < n; i++) {
        cin >> v[i];
    }

// Вычисляем размер дерева отрезков
    long long segtree_size = 2*pow(2, ceil(log2(n))) - 1;
    segtree.resize(segtree_size);

// Построение дерева отрезков
    build_segtree(0, 0, n-1);

    long long t;
    cin >> t;
    while(t--) {
        char op;
        cin >> op;
        if (op == 'a') {
            // Обработка запроса на сумму элементов на участке массива
            long long l, r;
            cin >> l >> r;
            cout << query_segtree(0, 0, n-1, l, r) << endl;
        } else {
            // Обработка запроса на обновление значения элементов на участке массива
            long long l, r, val;
            cin >> l >> r >> val;
            for (long long i = l; i <= r; i++) {
                update_segtree(0, 0, n-1, i, val);
            }
        }
    }
    return 0;
}