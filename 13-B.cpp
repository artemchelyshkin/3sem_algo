/*
Задано целое число N (4≤N≤106). Найти сумму наименьших 
простых делителей всех составных чисел, больших 2 и не превосходящих N.
*/
#include <iostream>
#include <cstdint>
#include <vector>

int64_t p = 1000000007; // const

std::vector<uint64_t> primes; // глобально лучше определять только константы
std::vector<uint64_t> mind;

void sieve(uint64_t n) {
  for (uint64_t k = 2; k < n + 1; ++k) {
    if (mind[k] == k) {
      primes.push_back(k);
    }
    for (uint32_t i = 0; i < primes.size() && (primes[i] * k <= n && primes[i] <= mind[k]); ++i) {
      mind[primes[i] * k] = primes[i];
    }
  }
}

void calc() {
  uint64_t n = 0;
  std::cin >> n;
  for (uint64_t i = 0; i < n + 2; ++i) {
    mind.push_back(i);
  }
  sieve(n);
  uint64_t sum = 0;
  for (uint64_t i = 2; i < n + 2; ++i) {
    if (mind[i] != i) {
      sum += mind[i];
    }
  }
  std::cout << sum;
}

int main() {
  calc();
}
