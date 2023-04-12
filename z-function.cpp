#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для вычисления Z-функции строки
vector<int> z_function(const string& s) {
    int n = s.length();
    vector<int> z(n, 0);

    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    // Входные данные: строка s
    string s; cin >> s;

    // Вычисление Z-функции строки s
    vector<int> z = z_function(s);

    // Вывод Z-функции на экран
    cout << "Z-функция для строки s:\n";
    for (int zi : z) {
        cout << zi << ' ';
    }
    cout << '\n';

    return 0;
}
