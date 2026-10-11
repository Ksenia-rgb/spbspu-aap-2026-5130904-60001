#include <iostream>
int main(){
  int a = 0; 
  std::cin >> a;
  if (a == 0) {
    std::cout << "Количество элементов, равных минимальному значению последовательности: 0\n";
    std::cout << "Количество элементов после максимума последовательности: 0\n";
    return 0;
  }
  int min = a;
  int max = a;
  int cnt1 = 1;
  int cnt2 = 0;
  while(a != 0){
    if(a < min){
      min = a;
      cnt1 = 0;
    } else if(a == min){
      cnt1++;
    }
    if(a > max){
      max = a;
      cnt2 = 0;
    } else {
      cnt2 ++;
    }
    std::cin >> a;
    if (std::cin.fail()){
    std::cerr << "ERROR";
    return 1;
    }
  }
  std::cout << "Количество элементов, равных минимальному значению последовательности: " << cnt1 << "\n";
  std::cout << "Количество элементов после максимума последовательности: " << cnt2 << "\n"; 
}
