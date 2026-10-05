#include <iostream>

int main() {
 int n = 1;
 while(n!=0) {

    std::cin >> n;

    if (std::cin.fail()) {
    std::cout << "Число не распознано\n";
    return 1;
    }
 }
 std::cout << n << "\n";
 return 0;
}
