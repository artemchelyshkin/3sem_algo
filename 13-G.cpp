/*
Даны два многочлена
A(x)=anxn+an−1xn−1+⋯+a0
B(x)=bmxm+bm−1xm−1+⋯+b0
Вычислите C(x)=A(x)⋅B(x)
*/
#include <iostream>
#include <cstdint>
#include <complex>
#include <vector>

#define pi 3.141592653589793238462643383279

// на лекции показывалось, как развернуть рекурсию
void FFT(std::vector<std::complex<double> >& data, bool reverse) {
  // преобразование Фурье, reverse = true  - обратное преобразование Фурье
  // делим наш маасив на 2 части, для каждого преобразование рекурсивно
  if (data.size() == 1) {
    return;
  }
  std::vector<std::complex<double> > data1;
  std::vector<std::complex<double> > data2;
  for (size_t i = 0; i < data.size(); i += 2) {
    data1.push_back(data[i]);
    data2.push_back(data[i + 1]);
  }
  FFT(data1, reverse), FFT(data2, reverse);
  double angle = 2 * pi / data.size() * (reverse ? -1 : 1);
  std::complex<double> wi(cos(angle), sin(angle));
  std::complex<double> w(1);
  for (size_t i = 0; i < data.size() / 2; ++i) {
    data[i] = data1[i] + w * data2[i];
    data[i + data.size() / 2] = data1[i] - w * data2[i];
    if (reverse) {
      data[i] /= 2;
      data[i + data.size() / 2] /= 2;
    }
    w *= wi;
  }
}

std::vector<int32_t> multiply(std::vector<int32_t>& a, std::vector<int32_t>& b) {
  uint32_t size = 1;
  while (size < std::max(a.size(), b.size())) {
    size <<= 1;
  }
  size <<= 1;
  std::vector<std::complex<double> > A;
  std::vector<std::complex<double> > B;
  A.assign(size, std::complex<double>(0, 0));
  B.assign(size, std::complex<double>(0, 0));
  for (uint32_t i = 0; i < a.size(); ++i) {
    A[i] = std::complex<double>(a[i], 0);
  }
  for (uint32_t i = 0; i < b.size(); ++i) {
    B[i] = std::complex<double>(b[i], 0);
  }
  FFT(A, false);
  FFT(B, false);
  for (uint32_t i = 0; i < A.size(); ++i) {
    A[i] *= B[i];
  }
  FFT(A, true);
  std::vector<int32_t> res;
  for (uint32_t i = 0; i < a.size() + b.size() - 1; ++i) {
    res.push_back(static_cast<int32_t>(A[i].real() + ((A[i].real() > 0) ? 1 : -1) * 0.5));
  }
  return res;
}


int main() {
  uint32_t n = 0;
  std::cin >> n;
  std::vector<int32_t> A;
  for (uint32_t i = 0; i < n + 1; ++i) {
    int32_t elem = 0;
    std::cin >> elem;
    A.push_back(elem);
  }
  uint32_t m = 0;
  std::cin >> m;
  std::vector<int32_t> B;
  for (uint32_t i = 0; i < m + 1; ++i) {
    int32_t elem = 0;
    std::cin >> elem;
    B.push_back(elem);
  }
  auto res = multiply(A, B);
  std::cout << A.size() - 1 + B.size() - 1 << " ";
  for (uint32_t i = 0; i < res.size(); ++i) {
    std::cout << res[i] << " ";
  }
}
