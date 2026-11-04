#include <iostream>
#include <cstring>
#include <cctype>


//1 функция  LAT-RMV
//char* str_2 = new char[capacity]
char* remove_latin (char* str_2, const char* str, size_t length) {
    size_t length_2 = 0;
    for (size_t i = 0; i < length; ++i) {
        if (std::isalpha(str[i]) && ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))) {
            continue;
        } 
        else {
            str_2[length_2] = str[i];
            ++length_2;
        }
    }
    str_2[length_2] = '\0';
    return str_2;
}

int main()
{
    size_t capacity = 4;
    size_t length = 0;
    char* str = new char[capacity];
    char symbol;

    while (std::cin.get(symbol) && symbol != '\n') {
        if (length == capacity - 1) {
            size_t& capacity_ref = capacity;
            capacity_ref *= 2;
            char* new_str = new char[capacity_ref];
            for (size_t i = 0; i < length; ++i) {
                new_str[i] = str[i];
            }
            delete[] str; 
            str = new_str;
        }
        str[length] = symbol;
        ++length;
    }
    str[length] = '\0';
    char* str_2 = new char[capacity];
    //вызов функции 1
    //вызов функции 2
}
