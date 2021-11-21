/*
Найдите z-функцию заданной строки s.
*/
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

void z_func(const string& str) {
  vector<size_t> z_function(str.size(), 0);
  size_t l = 0, r = 0;
  cout << 0 << " ";
  for (size_t i = 1; i < str.size(); ++i) {
    if (l <= i && i <= r) {
      z_function[i] = std::min(r - i + 1, z_function[i - l]);
    }
    while (z_function[i] + i < str.size() && str[i + z_function[i]] == str[z_function[i]]) {
      z_function[i]++;
    }
    if (i + z_function[i] > r) {
      l = i;
      r = i + z_function[i] - 1;
    }
    cout << z_function[i] << " ";
  }
}

int main() {
  string str;
  cin >> str;
  z_func(str);
}
