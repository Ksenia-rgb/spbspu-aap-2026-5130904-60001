#ifndef MATRIX_HPP
#define MATRIX_HPP

namespace sharov {
  constexpr int MAX_STACK_ELEMENT_COUNT = 10000;

  enum class StorageKind { fixed, dynamic };

  class FixedMatrixStorage {
  public:
    FixedMatrixStorage();

    long long *getData();
    const long long *getData() const;
    int getCapacity() const;

  private:
    long long data_[MAX_STACK_ELEMENT_COUNT];
  };

  class DynamicMatrixStorage {
  public:
    explicit DynamicMatrixStorage(int elementCount);
    DynamicMatrixStorage(const DynamicMatrixStorage &other) = delete;
    DynamicMatrixStorage &operator=(const DynamicMatrixStorage &other) = delete;
    ~DynamicMatrixStorage();

    bool isAllocated() const;
    long long *getData();
    const long long *getData() const;
    int getCapacity() const;

  private:
    long long *data_;
    int capacity_;
  };

  class Matrix {
  public:
    Matrix(long long *data, int rows, int columns);

    int getRows() const;
    int getCols() const;
    int getElementCount() const;
    long long *getData();
    const long long *getData() const;
    long long &at(int row, int column);
    const long long &at(int row, int column) const;

  private:
    long long *data_;
    int rows_;
    int columns_;
  };
}

#endif
