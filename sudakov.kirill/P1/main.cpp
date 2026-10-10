#include <iostream>
int main(){
    size_t n =1;
    size_t m =-10000000;
    int max_len = 0;
    int c = 1;
    while(n!=0){
        std::cin >> n;
        // Проверки
        if (std::cin.fail()) {
            std::cerr << "Ошибка ввода\n";
            return 1;
        }
        if (n>=m) ++c;
        if (c>max_len){ 
                max_len = c;
        }
        if (n<m){
            c = 1;
        }
        m = n;
        }
    
    std::cout << max_len;



}
