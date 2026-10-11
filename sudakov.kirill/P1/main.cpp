#include <iostream>
int main(){
    int n =1;
    int m =-2147483647;
    int max_len = 0;
    int loc_min = 2147483647;
    int c = 0;
    while(true){
        std::cin >> n;
        if (std::cin.fail()) {
            std::cerr << "Ошибка ввода\n";
            return 1;
        }
        if (n==0) break;
        if (n<loc_min) loc_min=n;   
        if (n>=m) ++c;
        if (c>max_len){ 
                max_len = c;
        }
        if (n<m){
            c = 1;
        }
        m = n;
        }
    
    std::cout << max_len << "\n";
    std::cout << loc_min << "\n";



}
