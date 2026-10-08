#include <iostream>

int main() {
    long long a = 0, b = 0, c = 0, max = 0;
    int i = 0;
    while (true) {
        std::cin >> a;
        if (a == 0) {
            break;
        }
        std::cin >> b;
        if (b == 0) {
            break;
        }
        std::cin >> c;
        if (c == 0) {
            break;
        }
        if (((a * a + b * b == c * c) || (a * a + c * c == b * b) || (b * b + c * c == a * a)) && (a > 0 && b > 0 && c > 0)) {
            i++;
        }
    std::cout << "Кол-во пифагоровых троек: " << i << "\n";
    return 0;
    }
}
