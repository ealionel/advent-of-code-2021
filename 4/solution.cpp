#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> split(const string& s, char delim) {
    vector<int> res;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        res.push_back(stoi(item));
    }

    return res;
}

void mark(vector<vector<int>>& board, int n) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == n) {
                board[i][j] = -1;
            }
        }
    }
}

bool has_won(const vector<vector<int>>& board) {
    for (int i = 0; i < 5; i++) {
        int cnt = 0;
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == -1) cnt++;
        }

        if (cnt == 5) return true;
    }

    for (int i = 0; i < 5; i++) {
        int cnt = 0;
        for (int j = 0; j < 5; j++) {
            if (board[j][i] == -1) cnt++;
        }

        if (cnt == 5) return true;
    }

    return false;
}

int sum_unmarked(const vector<vector<int>>& board) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] != -1) sum += board[i][j];
        }
    }

    return sum;
}

void print_board(const vector<vector<int>>& board) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    string first;
    cin >> first;

    vector<int> numbers = split(first, ',');

    int input;
    vector<vector<vector<int>>> boards;

    while (cin) {
        vector<vector<int>> board(5);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> input;
                board[i].push_back(input);
            }
        }

        boards.push_back(board);
    }

    boards.pop_back();

    int k = 0;
    bool finished = false;

    int answer_1 = -1;
    int answer_2 = -1;

    unordered_set<int> already_won;

    while (!finished && k < numbers.size()) {
        int v = numbers[k];
        cout << "(" << k << ") number = " << v << endl;

        for (int i = 0; i < boards.size(); i++) {
            if (already_won.find(i) != already_won.end()) {
              continue;
            }

            mark(boards[i], v);

            if (has_won(boards[i])) {
                already_won.insert(i);
                // finished = true;
                int sum = sum_unmarked(boards[i]);
                if (answer_1 == -1) {
                    answer_1 = sum * v;
                }

                print_board(boards[i]);

                answer_2 = sum * v;
            };
        }

        k++;
    }

    cout << "Answer (part 1): " << answer_1 << endl;
    cout << "Answer (part 2): " << answer_2 << endl;
}