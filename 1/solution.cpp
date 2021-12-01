#include <iostream>
#include <deque>
using namespace std;

int main () {
  int prev;
  cin >> prev;

  int current;

  int counter = 0;


  deque<int> q;
  q.push_back(prev);
  int queue_sum = prev;
  int counter_two = 0;

  while (cin >> current) {
    // Part one :
    if (current > prev) {
      counter++;
    }

    prev = current;

    // Part two :
    int prev_queue_sum = queue_sum;
    q.push_back(current);
    queue_sum += current;

    if (q.size() == 4) {
      queue_sum -= q.front();
      q.pop_front();
      
      if (queue_sum > prev_queue_sum) {
        counter_two++;
      }
    }
  }

  cout << "Part 1 answer : " << counter << endl;
  cout << "Part 2 answer : " << counter_two << endl;

  return 0;
}