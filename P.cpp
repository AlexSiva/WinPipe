#include <iostream>
#include <sstream>
#include <string>

int main() {
  int x;
  std::string str;
  std::getline(std::cin, str);
  std::stringstream ss(str);
  while (ss >> x) {
    std::cout << x * x * x << " ";
  }
  std::cout << "\n";
  return 0;
}