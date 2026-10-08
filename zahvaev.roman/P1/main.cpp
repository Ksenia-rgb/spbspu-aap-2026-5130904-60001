#include <iostream>

int main() {
    long long a, b, c, m = 0;
    int i = 0, ii = 0, n = 0;
    while (true) {
        std::cin >> a;
        if (std::cin.fail()) {
            std::cerr << "Input error\n";
            return 1;
        }
        if (a == 0) {
            break;
        }
        n++;
        if (n == 1 || a > m) {
            m = a;
            ii = 0;
        }
        else {
            ii++;
        }
        std::cin >> b;
        if (std::cin.fail()) {
            std::cerr << "Input error\n";
            return 1;
        }
        if (b == 0) {
            break;
        }
        n++;
        if (b > m) {
            m = b;
            ii = 0;
        }
        else {
            ii++;
        }
        std::cin >> c;
        if (std::cin.fail()) {
            std::cerr << "Input error\n";
            return 1;
        }
        if (c == 0) {
            break;
        }
        n++;
        if (c > m) {
            m = c;
            ii = 0;
        }
        else {
            ii++;
        }
        if (a > 0 && b > 0 && c > 0 && ((a * a + b * b == c * c) || (a * a + c * c == b * b) || (b * b + c * c == a * a))) {
            i++;
        }
    }
    std::cout << i << "\n";
    if (n == 0) {
        std::cerr << "Sequence is too short\n";
        return 2;
    }
    std::cout << ii << "\n";
    return 0;
}
