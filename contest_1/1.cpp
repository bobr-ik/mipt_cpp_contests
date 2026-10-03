#include <iostream>

struct MinMaxData {
  int min_temp{};
  int max_temp{};
};

double AvgTemp(const int* temp, int n);
MinMaxData MinMax(const int* temp, int n);
int HowMuchOverZero(const int* temp, int n);

int main() {
  int n{};
  std::cin >> n;

  if (n <= 0) return 0;

  int* temp = new int[n]();
  
  for (int i = 0; i < n; i++) {
    std::cin >> temp[i];
  }

  double ans1{AvgTemp(temp, n)};
  MinMaxData ans2{MinMax(temp, n)};
  int ans3{HowMuchOverZero(temp, n)};

  std::cout << std::fixed;
  std::cout.precision(1);

  std::cout << ans1 << '\n';
  std::cout << ans2.min_temp << ' ' << ans2.max_temp << '\n';
  std::cout << ans3 << '\n';

  delete[] temp;
}


double AvgTemp(const int* temp, int n) {
  double sum{0};
  for (int i = 0; i < n; i++) {
    sum += temp[i];
  }
  return sum / n;
}

MinMaxData MinMax(const int* temp, int n) {
  MinMaxData ans;
  ans.min_temp = temp[0];
  ans.max_temp = temp[0];

  for (int i = 1; i < n; i++) {
    ans.min_temp = ans.min_temp > temp[i] ? temp[i] : ans.min_temp;
    ans.max_temp = ans.max_temp < temp[i] ? temp[i] : ans.max_temp;
  }

  return ans;
}

int HowMuchOverZero(const int* temp, int n) {
  int counter{0};
  for (int i = 0; i < n; i++) {
    if (temp[i] < 0) {
      counter += 1;
    }
  }
  return counter;
}