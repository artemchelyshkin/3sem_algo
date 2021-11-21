/*
Постройте суффиксный массив для заданной строки s.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

void sort_substr_degree_of_two(const string& str, vector<int>& c, vector<size_t>& p,
  vector<size_t>& p2, int number_of_equivalent_classes,
  vector<int>& classes, size_t iter) {
  // выход - когда размер подстрок больше самой строки
  if (iter >= str.size()) {
    return;
  }
  // сортируем 2 половины подстрок длины 2^(i + 1)
  for (size_t i = 0; i < str.size(); ++i) {
    if (p[i] < iter) {
      p2[i] = str.size() + p[i] - iter;
    }
    else {
      p2[i] = p[i] - iter;
    }
  }
  // сортировка подсчетом, идем снизу вверх, чтобы не нарушать порядок,
  // смотрим, в каком классе находится та или иная строка, кладем ее на место
  // указанное в массиве classes - 1. Уменьшаем это значение
  // результат этого цикла - массив p для подстрок 2 ^ (i + 1)
  for (size_t i = p2.size(); i >= 1; i--) {
    int numb_of_class = c[p2[i - 1]];
    classes[numb_of_class]--;
    p[classes[numb_of_class]] = p2[i - 1];
  }
  // обновляем массив c и classes
  number_of_equivalent_classes = 0;
  int second_number = c[(p[0] + iter) % str.size()];
  int first_number = c[p[0]];
  vector<int> new_c(str.size(), 0);
  for (size_t i = 0; i < str.size(); ++i) {
    if ((first_number != c[p[i]]) || (second_number != c[(p[i] + iter) % str.size()])) {
      classes[number_of_equivalent_classes] = i;
      number_of_equivalent_classes++;
      first_number = c[p[i]];
      second_number = c[(p[i] + iter) % str.size()];
    }
    new_c[p[i]] = number_of_equivalent_classes;
  }
  classes[number_of_equivalent_classes] = str.size();
  number_of_equivalent_classes++;
  c = new_c;
  iter *= 2;
  sort_substr_degree_of_two(str, c, p, p2, number_of_equivalent_classes, classes, iter);
}

void suff_array(const string& str, vector<int>& c, vector<size_t>& p,
  vector<size_t>& p2, int number_of_equivalent_classes,
  vector<int>& classes) {
  // Совершаем нулевой шаг, отсортировываем символы, распределяем их по классам
  // эквивалентности, вызываем рекурсивную функцию
  for (size_t i = 0; i < str.size(); ++i) {
    p.push_back(i);
  }
  c.assign(str.size(), 0);
  p2.assign(str.size(), 0);
  classes.assign(str.size(), 0);
  std::sort(p.begin(), p.end(), [&str](int i, int j) { return str[i] < str[j]; });
  char prev_symb = '$';
  number_of_equivalent_classes = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (prev_symb == str[p[i]]) {
      c[p[i]] = number_of_equivalent_classes;
    }
    else {
      classes[number_of_equivalent_classes] = i;
      number_of_equivalent_classes++;
      prev_symb = str[p[i]];
      c[p[i]] = number_of_equivalent_classes;
    }
  }
  classes[number_of_equivalent_classes] = str.size();
  number_of_equivalent_classes++;
  sort_substr_degree_of_two(str, c, p, p2, number_of_equivalent_classes, classes, /*iter = */ 1);
  return;
}

void make_lcp(string& str, vector<int>& lcp, vector<int>& c, vector<size_t>& p) {
  // находим наибольшие общие подстроки
  lcp.assign(str.size(), 0);
  int curr_lcp = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (c[i] != str.size() - 1) {
      size_t next = p[c[i] + 1];
      while (std::max(i, next) + curr_lcp < str.size() &&
        str[i + curr_lcp] == str[next + curr_lcp]) {
        curr_lcp++;
      }
      lcp[c[i]] = curr_lcp;
      curr_lcp = std::max(0, curr_lcp - 1);
    }
  }
}

void number_of_substrings(string str) {
  vector<size_t> p; // отсортированный массив подстрок этой строки длины 2^i
  vector<size_t> p2; // вспомогательный массив для отсортированных 2 половин строк 2^(i + 1)
  vector<int> c; // массив  классов эквивалентности
  vector<int> classes; // массив, нужный для сортировки подсчетом. На i  позиции содержит кумулятивную сумму кол-ва
           // подстрок класса эквивалентности i
  vector<int> lcp; // на i позиции - наибольшая общая подстрока суффикса из i и из i + 1
  size_t iter = 1; // длина рассматриваемых подстрок
  int number_of_equivalent_classes = 0; // количество классов эквивалентности
  suff_array(str, c, p, p2, number_of_equivalent_classes, classes);
  make_lcp(str, lcp, c, p);
  // считаем результат и выводим его
  for (size_t i = 1; i < p.size(); ++i) {
    cout << p[i] + 1 << " ";
  }
}

int main() {
  string str;
  cin >> str;
  str += '$';
  number_of_substrings(str);
}
