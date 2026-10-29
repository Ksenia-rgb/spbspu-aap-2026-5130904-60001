#include <iostream>

int findMaxLength() {
    int prev = 0;
    int num = 0;
    int len = 0;
    int maxLen = 0;
    bool first = true;
    bool zero = false;

    while (std::cin >> num) {
        if (num == 0) {
            zero = true;
            break;
        }

        if (first) {
            len = 1;
            first = false;
        } else if (num >= prev) {
            len++;
        } else {
            len = 1;
        }

        if (len > maxLen) {
            maxLen = len;
        }

        prev = num;
    }

    if (!zero) {
        std::cerr << "Error: invalid input" << std::endl;
        return -1;
    }

    std::cout << maxLen << std::endl;
    return 0;
}

int main() {
    return findMaxLength() == -1 ? 1 : 0;
}
