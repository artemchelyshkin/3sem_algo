/*
Даны три выпуклых многоугольника-города. В каждом их них можно поставить по алтарю. 
Тогда церковь должна располагаться в точке, равной центру масс этих трёх точек-алтарей. 
Для q запросов определите, можно ли так поставить алтари, чтобы церковь находилась в заданной точке.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>

using std::cin;
using std::cout;
using std::vector;

struct point {
  int64_t x, y;

  point() {}

  point(int64_t x, int64_t y) :x(x), y(y) {}

  point operator + (const point& another) {
    return point(x + another.x, y + another.y);
  }

  point operator - (const point& another) {
    return point(x - another.x, y - another.y);
  }
};

int64_t vec_mul(point& one, point& two) {
  return one.x * two.y - one.y * two.x;
}

vector<point> shift_min(const vector<point>& A) {
  int64_t y = INT_MAX, x = INT_MAX;
  int64_t min_res = -1;
  for (uint64_t i = 0; i < A.size(); ++i) {
    if ((A[i].x < x) || (A[i].x == x && A[i].y < y)) {
      x = A[i].x, y = A[i].y;
      min_res = i;
    }
  }
  vector<point> newA;
  for (uint64_t i = 0; i < A.size(); ++i) {
    newA.push_back(A[(min_res + i) % A.size()]);
  }
  return newA;
}

bool check_in_tr(point A, point B, point C, point pt) {
  point OA = pt - A;
  point OB = pt - B;
  point OC = pt - C;
  point BA = B - A;
  point CB = C - B;
  point AC = A - C;
  int64_t res1 = vec_mul(OA, BA), res2 = vec_mul(OB, CB), res3 = vec_mul(OC, AC);
  if (res1 >= 0 && res2 >= 0 && res3 >= 0) {
    return true;
  }
  if (res1 <= 0 && res2 <= 0 && res3 <= 0) {
    return true;
  }
  return false;
}

bool is_point_inside_figure(vector<point>& A, point pt) {
  point tmp1 = A[1] - A[0];
  point tmp2 = A[A.size() - 1] - A[0];
  point tmp3 = pt - A[0];
  int64_t res1 = vec_mul(tmp1, tmp3), res2 = vec_mul(tmp2, tmp3);
  if (res1 < 0 || res2 > 0) {
    return false;
  }
  uint64_t start = 0, finish = A.size() - 1;
  while (true) {
    uint64_t iter = start + (finish - start) / 2;
    if (iter == A.size() - 1) {
      return false;
    }
    point tmp1 = A[iter] - A[0];
    point tmp2 = A[iter + 1] - A[0];
    point tmp3 = pt - A[0];
    int64_t res1 = vec_mul(tmp1, tmp3), res2 = vec_mul(tmp2, tmp3);
    if (res1 >= 0 && res2 <= 0) {
      return check_in_tr(A[0], A[iter], A[iter + 1], pt);
    }
    if (iter == 0) {
      return false;
    }
    if (res1 < 0) {
      finish = iter;
    }
    if (res2 > 0) {
      start = iter;
    }
  }

}

vector<point> minkovskiy(vector<point>& A, vector<point>& B) {
  uint64_t current_point = 0;
  vector<point> AandB;
  A = shift_min(A), B = shift_min(B);
  uint64_t n = A.size(), m = B.size();
  uint64_t i = 0, j = 0;
  A.push_back(A[0]), A.push_back(A[1]);
  B.push_back(B[0]), B.push_back(B[1]);
  while (i < n || j < m) {
    AandB.push_back(A[i] + B[j]);
    point vec1 = A[i + 1] - A[i];
    point vec2 = B[j + 1] - B[j];
    if (vec_mul(vec1, vec2) > 0) {
      ++i;
    }
    else {
      if (vec_mul(vec2, vec1) > 0) {
        ++j;
      }
      else {
        ++i, ++j;
      }
    }
  }
  return AandB;
}

void calc(vector<point>& A) {
  uint64_t f = 0;
  cin >> f;
  vector<bool> res;
  for (uint64_t i = 0; i < f; ++i) {
    int64_t x = 0, y = 0;
    cin >> x >> y;
    x *= 3, y *= 3;
    point pt(x, y);
    res.push_back(is_point_inside_figure(A, pt));
  }
  for (uint64_t i = 0; i < res.size(); ++i) {
    cout << ((res[i]) ? "YES" : "NO") << '\n';
  }
}

int main() {
  vector<point> A, B, C;
  uint64_t n = 0;
  cin >> n;
  for (uint64_t i = 0; i < n; ++i) {
    int64_t x = 0, y = 0;
    cin >> x >> y;
    A.push_back(point(x, y));
  }
  uint64_t m = 0;
  cin >> m;
  for (uint64_t i = 0; i < m; ++i) {
    int64_t x = 0, y = 0;
    cin >> x >> y;
    B.push_back(point(x, y));
  }
  uint64_t k = 0;
  cin >> k;
  for (uint64_t i = 0; i < k; ++i) {
    int64_t x = 0, y = 0;
    cin >> x >> y;
    C.push_back(point(x, y));
  }
  auto AB = minkovskiy(A, B);
  auto ABC = minkovskiy(AB, C);
  calc(ABC);
}
