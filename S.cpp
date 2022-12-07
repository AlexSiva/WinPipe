#include <iostream>
#include <sstream>
#include <string>

int main() {
  int x;
  int sum = 0;
  std::string str;
  std::getline(std::cin, str);
  std::stringstream ss(str);
  while (ss >> x) {
    sum += x;
  }
  std::cout << sum << "\n";
  return 0;
}