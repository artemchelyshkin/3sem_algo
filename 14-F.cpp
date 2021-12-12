/*
Дано N точек на плоскости. Нужно построить их выпуклую оболочку.
Гарантируется, что выпуклая оболочка является невырожденной.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;
using std::vector;
using std::stack;

struct point {
  int64_t x, y;

  point() {}

  point(int64_t x, int64_t y) : x(x), y(y) {}

  bool operator == (const point& another) {
    return this->x == another.x && this->y == another.y;
  }

  bool operator != (const point& another) {
    return !(*this == another);
  }

};

bool is_clockwise_rotation(point a, point b, point c) {
  int64_t res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  return (res > 0);
}

bool is_anticlockwise_rotation(point a, point b, point c) {
  int64_t res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  return (res < 0);
}

vector<point> andrew_algo(vector<point>& points) {
  // Сортируем точки в порядке возрастания x
  // Далее удаляем все повторяющиеся точки, 
  // запускаем алгоритм Эндрю, находя 2 пути, один
  // с правым поворотом, другой - с левым, затем соединяем полученные
  // пути
  std::sort(points.begin(), points.end(),
    [](const point& a, const point& b) { return a.x < b.x || a.x == b.x && a.y < b.y; });
  vector<point> tmp;
  point prev = points[0];
  tmp.push_back(prev);
  for (size_t i = 1; i < points.size(); ++i) {
    if (!(prev == points[i])) {
      tmp.push_back(points[i]);
      prev = points[i];
    }
  }
  points = tmp;
  point a = points[0], b = points.back();
  vector<point> up, down;
  up.push_back(a);
  down.push_back(a);
  for (size_t i = 1; i < points.size(); ++i) {
    if (i == points.size() - 1 || !(is_clockwise_rotation(b, a, points[i]))) {
      while (up.size() > 1 && !is_clockwise_rotation(up.back(), up[up.size() - 2], points[i])) {
        up.pop_back();
      }
      up.push_back(points[i]);
    }
    if (i == points.size() - 1 || !(is_anticlockwise_rotation(b, a, points[i]))) {
      while (down.size() > 1 && !is_anticlockwise_rotation(down.back(), down[down.size() - 2], points[i])) {
        down.pop_back();
      }
      down.push_back(points[i]);
    }
  }
  vector<point> perimeter;
  for (size_t i = 0; i < up.size(); ++i) {
    perimeter.push_back(up[i]);
  }
  for (size_t i = down.size() - 1; i > 0; i--) {
    perimeter.push_back(down[i]);
  }
  return perimeter;
}

void find_perimeter(vector<point>& points) {
  vector<point> perimeter = andrew_algo(points);
  point prev = points[0];
  vector<point> tmp;
  tmp.push_back(prev);
  for (size_t i = 1; i < perimeter.size(); ++i) {
    if (!(prev == perimeter[i])) {
      tmp.push_back(perimeter[i]);
      prev = perimeter[i];
    }
  }
  perimeter = tmp;
  std::cout << perimeter.size() << std::endl;
  std::cout << perimeter[0].x << " " << perimeter[0].y << '\n';
  for (size_t i = perimeter.size() - 1; i > 0; i--) {
    std::cout << perimeter[i].x << " " << perimeter[i].y << '\n';
  }
}

int main() {
  uint32_t n = 0;
  cin >> n;
  vector<point> points;
  for (uint32_t i = 0; i < n; ++i) {
    int64_t x = 0, y = 0;
    point new_dot;
    cin >> x >> y;
    new_dot.x = x, new_dot.y = y;
    points.push_back(new_dot);
  }
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  find_perimeter(points);
}
