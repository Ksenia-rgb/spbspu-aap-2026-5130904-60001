#include <iostream>

namespace zahovaev {
  struct words {
  public:
    words();
    words(const size_t size, const char field);
    words(const words & rhs);
    words(const char* rhs, size_t size);
    ~words();
    words & operator=(words && rhs) noexcept;
    words & operator=(const words & rhs);

    words expand();
    words add(char el);
    size_t getSize() const;
    size_t getCon() const;
    char getChar(const size_t i) const noexcept;
    char * getStr() const;
  private:
    char * the_words;
    size_t con_el;
    size_t size;
  };

  words::words():
    the_words(nullptr),
    con_el(0),
    size(0)
  {}

  words::words(const size_t size, const char field):
    size(size),
    con_el(size),
    the_words(new char[size])
  {
    for (size_t i = 0; i < size; i++) {
      the_words[i] = field;
    }
  }

  words::words(const words & rhs):
    size(rhs.size),
    the_words(new char[rhs.size]),
    con_el(rhs.con_el)
  {
    for (size_t i = 0; i < con_el; i++) {
      the_words[i] = rhs.the_words[i];
    }
  }

  words::words(const char* rhs, size_t size):
    size(size),
    the_words(new char[size]),
    con_el(size)
  {
    for (size_t i = 0; i < size; i++) {
      the_words[i] = rhs[i];
    }
  }

  words & words::operator=(words && rhs) noexcept
  {
    std::swap(the_words, rhs.the_words);
    std::swap(size, rhs.size);
    std::swap(con_el, rhs.con_el);
    return *this;
  }  

  words & words::operator=(const words & rhs)
  {
    words res(rhs);
    std::swap(the_words, res.the_words);
    std::swap(size, res.size);
    std::swap(con_el, res.con_el);
    return *this;
  }

  words::~words()
  {
    delete[] the_words;
  }

  words words::expand()
  {
    words res(size*2 + size == 0, '0');
    for (size_t i = 0; i < con_el; i++) {
      res.the_words[i] = the_words[i];
    }
    std::swap(the_words, res.the_words);
    std::swap(size, res.size);
    return *this;
  }

  words words::add(char el)
  {
    words res(*this);
    if (con_el >= size) {
      res = res.expand();
    }
    res.the_words[con_el++] = el;
    std::swap(the_words, res.the_words);
    std::swap(size, res.size);
    return *this;
  }

  size_t words::getSize() const
  {
    return size;
  }

  size_t words::getCon() const
  {
    return con_el;
  }

  char words::getChar(const size_t i) const noexcept
  {
    return the_words[i];
  }

  char * words::getStr() const
  {
    return the_words;
  }

 void uniTwo(const char * str1, const size_t size1, const char * str2, const size_t size2, char * buff) noexcept
  {
    size_t min_size = size1;
    size_t max_size = size2;
    const char * max_str = str2;
    if (size1 > size2) {
      min_size = size2;
      max_size = size1;
      max_str = str1;
    }
    size_t j = 0;
    size_t i = 0;
    for (; i < min_size; i++) {
      buff[j++] = str1[i];
      buff[j++] = str2[i];
    }
    for (; i < max_size; i++) {
      buff[j++] = max_str[i];
    }
  }
}

int main()
{
  try {
    char el = '0';
    zahovaev::words first_words;
    const zahovaev::words second_words("abvgd ef123", 11); 
    while (std::cin >> std::noskipws >> el && el != '\n') {
      first_words.add(el);
    }
    if (!std::cin) {
      std::cerr << "What do you do with my stdin((";
    }
    zahovaev::words third_words(first_words.getCon() + second_words.getCon(), '0');
    zahovaev::uniTwo(first_words.getStr(), first_words.getCon(), second_words.getStr(), second_words.getCon(), third_words.getStr());
    std::cout << third_words.getCon() << "\n";
    for (size_t i = 0 ; i < third_words.getCon(); i++) {
      std::cout << third_words.getChar(i);
    }
    std::cout << "\n";
  } catch(...) {
    std::cerr << "Bad allocation";
    return 1;
  } catch(...) {
    std::cerr << "Your string too big";
    return 1;
  }
}
