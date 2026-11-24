#ifndef CHARACTERISTICS_HPP
#define CHARACTERISTICS_HPP

namespace sharov {
  bool isNonIncreasingStep(int previous, int current);
  bool isLocalMaximum(int left, int middle, int right);

  class SequenceCharacteristics {
  public:
    SequenceCharacteristics();

    void add(int value);

    int getSize() const;
    int getMonDec() const;
    bool isLocMaxDefined() const;
    int getLocMax() const;

  private:
    int previous_;
    int beforePrevious_;
    int size_;
    int currentDecLength_;
    int maxDecLength_;
    int locMaxCount_;
  };
}

#endif
