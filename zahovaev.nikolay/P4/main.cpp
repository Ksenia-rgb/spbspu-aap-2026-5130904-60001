#include <iostream>
namespace zahovaev {
  struct string {
    const char * theString;
    size_t size;

    string expand()
    {
      string string2 = string(); // construct with size*2
      for (size_t i = 0; i < this->size; i++) {
        string2[i] = this->string[i];
      }
      return string2;
    }

    string add(char el, size_t i)
    {
      while (i >= this->size) {
        try {
          this->theString = expand();
          
        } except(...) {
          throw
        }
      } else {
        this->theString[i] = el;
      }
    }
  };
}
using namespace zahovaev;
int main()
{
  string k = {"ab", 2};
  k.expand();
}
