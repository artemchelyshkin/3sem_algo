/*
Задано целое число N (4≤N≤106). Найти сумму наименьших
простых делителей всех составных чисел, больших 2 и не превосходящих N.
*/
#include <iostream>
#include <cstdint>
#include <vector>

const int64_t p = 1000000007;

struct Sieve {
  uint64_t n = 0;
  std::vector<uint64_t> primes;
  std::vector<uint64_t> mind;
};

void sieve(Sieve& sv) {
  for (uint64_t k = 2; k < sv.n + 1; ++k) {
    if (sv.mind[k] == k) {
      sv.primes.push_back(k);
    }
    for (uint32_t i = 0; i < sv.primes.size() && (sv.primes[i] * k <= sv.n && sv.primes[i] <= sv.mind[k]); ++i) {
      sv.mind[sv.primes[i] * k] = sv.primes[i];
    }
  }
}

void calc() {
  uint64_t n = 0;
  std::cin >> n;
  Sieve sv;
  sv.n = n;
  for (uint64_t i = 0; i < n + 2; ++i) {
    sv.mind.push_back(i);
  }
  sieve(sv);
  uint64_t sum = 0;
  for (uint64_t i = 2; i < n + 2; ++i) {
    if (sv.mind[i] != i) {
      sum += sv.mind[i];
    }
  }
  std::cout << sum;
}

int main() {
  calc();
}
