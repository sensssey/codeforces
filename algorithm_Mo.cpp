#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Query {
    int left;
    int right;
    int index;
};

bool compare(const Query& a, const Query& b) {
    int block_a = a.left / sqrt(a.right - a.left + 1);
    int block_b = b.left / sqrt(b.right - b.left + 1);

    if (block_a != block_b) {
        return block_a < block_b;
    }
    return a.right < b.right;
}

vector<int> mo_algorithm(const vector<int>& arr, vector<Query>& queries) {
    sort(queries.begin(), queries.end(), compare);

    vector<int> answers(queries.size());

    int current_left = 0;
    int current_right = -1;
    int current_sum = 0;

    for (const Query& query : queries) {
        while (current_left > query.left) {
            current_sum += arr[--current_left];
        }
        while (current_right < query.right) {
            current_sum += arr[++current_right];
        }
        while (current_left < query.left) {
            current_sum -= arr[current_left++];
        }
        while (current_right > query.right) {
            current_sum -= arr[current_right--];
        }

        answers[query.index] = current_sum;
    }

    return answers;
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int q;
    cin >> q;

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].left >> queries[i].right;
        queries[i].index = i;
    }

    vector<int> answers = mo_algorithm(arr, queries);

    for (int answer : answers) {
        cout << answer << endl;
    }

    return 0;
}
