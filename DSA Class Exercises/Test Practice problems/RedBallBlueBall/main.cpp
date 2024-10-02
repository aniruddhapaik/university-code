#include <iostream>
#include <queue>
#include <string>

using namespace std;

void stack_balls(int N) {
  queue<string> Q1, Q2;
  for (int i = 0; i < N; ++i) {
    string ball = (i % 4 < 2) ? "red" : "blue";
    if (i % 2 == 0) {
      Q1.push(ball);
    } else {
      Q2.push(ball);
    }
  }

  cout << "Q1: ";
  while (!Q1.empty()) {
    cout << Q1.front() << " ";
    Q1.pop();
  }
  cout << endl;

  cout << "Q2: ";
  while (!Q2.empty()) {
    cout << Q2.front() << " ";
    Q2.pop();
  }
  cout << endl;
}

int main() {
  int N = 5;
  stack_balls(N);
  return 0;
}