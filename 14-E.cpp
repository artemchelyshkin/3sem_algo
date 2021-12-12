/*
Проверьте, лежит ли точка внутри многоугольника.
*/

#include <iostream>
#include <cstdint>
#include <cmath>
#include <iomanip>
#include <vector>

const double EPS = 0.0001;
const double pi = 3.1415926535897932;

struct point {
  double x, y;

  point() {}

  point(double x, double y) :x(x), y(y) {}

  point operator + (const point& another) {
    return point(x + another.x, y + another.y);
  }

  point operator - (const point& another) {
    return point(x - another.x, y - another.y);
  }
};

bool is_point_0_inside_figure(std::vector<point>& A) {
  // Проверяем расрположение точки (0, 0) относительно полученной фигуры
  // Если она внутри, то фигуры пересекаются. Посмотрим, сколько раз луч из
  // (0,0) || оси х пересечет наши ребра. Если четное число раз, значит точка снаружт
  // Иначе - внутри
  bool result = false;
  int s = A.size() - 1;
  for (int k = 0; k < A.size(); ++k) {
    if ((A[s].x == 0 && A[s].y == 0) || (A[k].x == 0 && A[k].y == 0)) {
      return true;
    }
    if (A[s].y == A[k].y) {
      if (A[s].y == 0) {
        if (std::max(A[s].x, A[k].x) > 0 && std::min(A[s].x, A[k].x) < 0) {
          return true;
        }
      }
      s = k;
      continue;
    }
    if (std::max(A[s].y, A[k].y) == 0) {
      if (A[s].y == 0) {
        if (A[s].x > 0) {
          result = !result;
          s = k;
          continue;
        }
        if (A[s].x == 0) {
          return true;
        }
      }
      else {
        if (A[k].x > 0) {
          result = !result;
          s = k;
          continue;
        }
        if (A[k].x == 0) {
          return true;
        }
      }
    }
    if (std::min(A[s].y, A[k].y) == 0) {
      s = k;
      continue;
    }
    if (std::min(A[s].y, A[k].y) < 0 && std::max(A[s].y, A[k].y) > 0) {
      point vec1 = A[s] - A[k];
      if (A[s].x - A[s].y * vec1.x / vec1.y > 0) {
        result = !result;
      }
      if (A[s].x - A[s].y * vec1.x / vec1.y == 0) {
        return true;
      }
    }
    s = k;
  }
  return result;
}

int main() {
  int32_t n = 0, l = 0, u = 0;
  std::cin >> n >> l >> u;
  point pt(l, u);
  std::vector<point> A;
  for (uint32_t i = 0; i < n; ++i) {
    int32_t a = 0, b = 0;
    std::cin >> a >> b;
    point p(a - l, b - u);
    A.push_back(p);
  }
  std::cout << (is_point_0_inside_figure(A) ? "YES" : "NO");
}
