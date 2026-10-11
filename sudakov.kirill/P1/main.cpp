#include <iostream>
int main(){
    int n =1;
    int m =-10000000;
    int max_len = 0;
    int c = 0;
    while(n!=0){
        std::cin >> n;
        //std::cout << n << "\n";
        // Проверки
        if (std::cin.fail()) {
            std::cerr << "Ошибка ввода\n";
            return 1;
        }
        if (n==0) break;
        //Алкоритм
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
