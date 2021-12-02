#include <iostream>
#include <string>
using namespace std;

int main () {
  string command;
  int val;

  int horizontal = 0;
  int vertical = 0;

  int depth = 0;
  int aim = 0;

  while (cin >> command) {
    cin >> val;

    if (command == "forward") {
      horizontal += val;
      depth += aim * val;
    } else if (command == "up") {
      vertical -= val;
      aim -= val;
    } else if (command == "down") {
      vertical += val;
      aim += val;
    }
  }

  cout << "Answer (part 1) : " << horizontal * vertical << endl;
  cout << "Answer (part 2) : " << horizontal * depth << endl;

  return 0;
}