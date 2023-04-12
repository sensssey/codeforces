#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для вычисления префикс-функции строки
vector<int> prefix_function(const string& s) {
    int n = s.length();
    vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

// Функция для поиска всех вхождений строки p в строке t с использованием алгоритма КМП
vector<int> kmp_search(const string& p, const string& t) {
    string combined = p + "#" + t;
    vector<int> pi = prefix_function(combined);
    vector<int> occurrences;

    for (int i = p.length() + 1; i < combined.length(); ++i) {
        if (pi[i] == p.length()) {
            occurrences.push_back(i - 2 * p.length());
        }
    }
    return occurrences;
}

int main() {
    string p, t;
    cin >> p >> t;
    // Вычисление всех вхождений строки p в строке t
    vector<int> occurrences = kmp_search(p, t);
    for (int pos : occurrences) {
        cout << pos << ' ';
    }
    cout << '\n';
    return 0;
}
