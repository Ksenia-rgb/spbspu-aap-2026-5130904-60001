#ifndef VARIANTS_HPP
#define VARIANTS_HPP

namespace sharov {
  constexpr const char *kActiveVariants[] = {"REP-DGT", "RMV-VOW"};

  static_assert(sizeof(kActiveVariants) / sizeof(kActiveVariants[0]) > 0,
      "TODO: replace the active variants with the ones assigned by the teacher");

  using VariantFunction = int (*)(const char *source, char *destination, int destinationCapacity);

  struct VariantEntry {
    const char *name;
    VariantFunction apply;
  };

  int getVariantCount();
  const VariantEntry *getVariants();
  int getActiveVariantCount();
  const char *getActiveVariant(int index);
  const VariantEntry *findVariant(const char *name);
  int applyVariant(const char *name, const char *src, char *dst, int dstCapacity);
}

#endif
