#include <iostream>

int main() {
    long long a = 0;
    long long b = 0;
    long long c = 0;
    int k10 = 0;

    long long m = 0;
    long long k12 = 0;

    int n = 0;

    while (std::cin >> c) {
        if (c == 0) {
            break;
        }

        n++;

        if (n >= 3) {
            if (b < a && b > c) {
                k10++;
            }
        }
        a = b;
        b = c;

        if (n == 1) {
            m = c;
            k12 = 0;
        } else if (c > m) {
            m = c;
            k12 = 0;
        } else {
            k12++;
        }
    }

    if (c != 0 || std::cin.fail()) {
        std::cerr << "Error: invalid input\n";
        return 1;
    }

    if (n == 0) {
        std::cerr << "Error: sequence is too short\n";
        return 2;
    }

    std::cout << k10 << "\n";
    std::cout << k12 << "\n";

    return 0;
}
