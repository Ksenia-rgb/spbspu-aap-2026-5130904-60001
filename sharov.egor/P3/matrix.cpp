#include "matrix.hpp"

#include <cstddef>
#include <new>

namespace sharov {
  FixedMatrixStorage::FixedMatrixStorage()
  {
    for (int index = 0; index < MAX_STACK_ELEMENT_COUNT; ++index) {
      data_[index] = 0;
    }
  }

  long long *FixedMatrixStorage::getData()
  {
    return data_;
  }

  const long long *FixedMatrixStorage::getData() const
  {
    return data_;
  }

  int FixedMatrixStorage::getCapacity() const
  {
    return MAX_STACK_ELEMENT_COUNT;
  }

  DynamicMatrixStorage::DynamicMatrixStorage(int elementCount):
    data_(nullptr),
    capacity_(0)
  {
    if (elementCount >= 0) {
      data_ = new (std::nothrow) long long[static_cast< std::size_t >(elementCount)];
      capacity_ = elementCount;
    }
  }

  DynamicMatrixStorage::~DynamicMatrixStorage()
  {
    delete[] data_;
  }

  bool DynamicMatrixStorage::isAllocated() const
  {
    return data_ != nullptr;
  }

  long long *DynamicMatrixStorage::getData()
  {
    return data_;
  }

  const long long *DynamicMatrixStorage::getData() const
  {
    return data_;
  }

  int DynamicMatrixStorage::getCapacity() const
  {
    return capacity_;
  }

  Matrix::Matrix(long long *data, int rows, int columns):
    data_(data),
    rows_(rows),
    columns_(columns)
  {}

  int Matrix::getRows() const
  {
    return rows_;
  }

  int Matrix::getCols() const
  {
    return columns_;
  }

  int Matrix::getElementCount() const
  {
    return rows_ * columns_;
  }

  long long *Matrix::getData()
  {
    return data_;
  }

  const long long *Matrix::getData() const
  {
    return data_;
  }

  long long &Matrix::at(int row, int column)
  {
    return data_[row * columns_ + column];
  }

  const long long &Matrix::at(int row, int column) const
  {
    return data_[row * columns_ + column];
  }
}
