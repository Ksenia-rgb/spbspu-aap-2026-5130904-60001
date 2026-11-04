#include <iostream>
#include <cstring>
#include <cctype>

int main()
{
    size_t capacity = 4;
    size_t length = 0;
    char* str = new char[capacity];
    char symbol;

    while (std::cin.get(symbol) && symbol != '\n') {
        if (length == capacity - 1) {
            capacity *= 2;
            char* new_str = new char[capacity];
            for (size_t i = 0; i < (capacity / 2); ++i) {
                new_str[i] = str[i];
            }
            delete[] str; 
            str = new_str;
        }
        str[length] = symbol;
        ++length;
    }
    str[length] = '\0';
}
