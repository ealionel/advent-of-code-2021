#include<iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void count_bits(vector<int>& counter, string number) {
  for (int i = 0; i < counter.size(); i++) {
    counter[i] += number[i] - '0';
  }
}

int count_ones_at(const vector<string>& all, int pos) {
  int counter = 0;

  for (auto s: all) {
    cout << s << endl;
    if (s[pos] == '1') counter++;
  }
  cout << endl;

  return counter;
}

int main() {

  string input;
  int total_input = 1;

  cin >> input;

  vector<int> counter(input.size(), 0);
  count_bits(counter, input);

  vector<string> all_input = { input };

  while (cin >> input) {
    count_bits(counter, input);
    total_input++;
    all_input.push_back(input);
  }

  int gamma = 0;
  int epsilon = 0;

  string gamma_str;
  string epsilon_str;

  for (auto v: counter) {
    epsilon <<= 1;
    gamma <<= 1;
    if (v > total_input / 2) {
      gamma += 1;
    } else {
      epsilon += 1;
    }
  }

  // part 2
  vector<string> copy_a(all_input);
  vector<string> copy_b(all_input);

  int a_res = 0;
  int b_res = 0;

  int cnt = 0;
  for (int i = 0; i < input.size(); i++) {
    char a;
    int ones_a = count_ones_at(copy_a, i);

    if (ones_a >= ceil((double) copy_a.size() / 2)) {
      a = '1';
    } else {
      a = '0';
    }
    
    cout << "ones a " << ones_a << "/" << copy_a.size() << " -> " << a <<endl;


    auto remove_a = remove_if(copy_a.begin(), copy_a.end(), [i, a](string s) {
      return s[i] != a;
    });

    copy_a.erase(remove_a, copy_a.end());

    cout << copy_a.size() << endl;

    if (copy_a.size() == 1) {
      cout << "a: " << stoi(copy_a[0], NULL, 2) << endl;
      a_res = stoi(copy_a[0], NULL, 2);
    }

    char b;
    int ones_b = count_ones_at(copy_b, i);
    if (ones_b < ceil((double) copy_b.size() / 2)) {
      b = '1';
    } else {
      b = '0';
    }

    cout << "ones b " << ones_b << "/" << copy_b.size() << " -> " << b << endl;
    auto remove_b = remove_if(copy_b.begin(), copy_b.end(), [i, b](string s) {
      return s[i] != b;
    });

    copy_b.erase(remove_b, copy_b.end());

    if (copy_b.size() == 1) {
      cout << "b: " << stoi(copy_b[0], NULL, 2) << endl;
      b_res = stoi(copy_b[0], NULL, 2);
    }
  }

  cout << "Answer (part 1): " << gamma * epsilon << endl;
  cout << "Answer (part 2): " << a_res * b_res << endl;

  return 0;
}