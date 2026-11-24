#include "characteristics.hpp"

namespace sharov {
  bool isNonIncreasingStep(int previous, int current)
  {
    return current <= previous;
  }

  bool isLocalMaximum(int left, int middle, int right)
  {
    return left < middle && middle > right;
  }

  SequenceCharacteristics::SequenceCharacteristics():
    previous_(0),
    beforePrevious_(0),
    size_(0),
    currentDecLength_(0),
    maxDecLength_(0),
    locMaxCount_(0)
  {}

  void SequenceCharacteristics::add(int value)
  {
    if (size_ == 0) {
      currentDecLength_ = 1;
    } else if (isNonIncreasingStep(previous_, value)) {
      ++currentDecLength_;
    } else {
      currentDecLength_ = 1;
    }
    if (currentDecLength_ > maxDecLength_) {
      maxDecLength_ = currentDecLength_;
    }
    const bool hasPreviousNeighbours = size_ >= 2;
    if (hasPreviousNeighbours && isLocalMaximum(beforePrevious_, previous_, value)) {
      ++locMaxCount_;
    }
    beforePrevious_ = previous_;
    previous_ = value;
    ++size_;
  }

  int SequenceCharacteristics::getSize() const
  {
    return size_;
  }

  int SequenceCharacteristics::getMonDec() const
  {
    return maxDecLength_;
  }

  bool SequenceCharacteristics::isLocMaxDefined() const
  {
    return size_ > 0;
  }

  int SequenceCharacteristics::getLocMax() const
  {
    return locMaxCount_;
  }
}
