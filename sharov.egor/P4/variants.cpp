#include "variants.hpp"

#include <cstring>

#include "string-ops.hpp"

namespace sharov {
  namespace {
    const VariantEntry kVariantTable[] = {
        {"SPC-RMV", spcRmv},
        {"DEC-RMV", decRmv},
        {"LAT-RMV", latRmv},
        {"CMN-SYM", cmnSym},
        {"UNC-SYM", uncSym},
        {"REP-SYM", repSym},
        {"DIF-LAT", difLat},
        {"HAS-REP", hasRep},
        {"SEQ-SYM", seqSym},
        {"RPL-SYM", rplSym},
        {"UPP-LOW", uppLow},
        {"UNI-TWO", uniTwo},
        {"HAS-SAM", hasSam},
        {"SHR-SYM", shrSym},
        {"EXC-SND", excSnd},
        {"DGT-SND", dgtSnd},
        {"REP-DGT", repDgt},
        {"RMV-VOW", rmvVow},
        {"FRQ-TOP", frqTop},
        {"LAT-TWO", latTwo},
    };

    constexpr int kVariantCount = static_cast< int >(sizeof(kVariantTable) / sizeof(kVariantTable[0]));
  }

  int getVariantCount()
  {
    return kVariantCount;
  }

  const VariantEntry *getVariants()
  {
    return kVariantTable;
  }

  int getActiveVariantCount()
  {
    return static_cast< int >(sizeof(kActiveVariants) / sizeof(kActiveVariants[0]));
  }

  const char *getActiveVariant(int index)
  {
    if (index < 0 || index >= getActiveVariantCount()) {
      return "";
    }
    return kActiveVariants[index];
  }

  const VariantEntry *findVariant(const char *const name)
  {
    for (int i = 0; i < kVariantCount; ++i) {
      if (std::strcmp(kVariantTable[i].name, name) == 0) {
        return &kVariantTable[i];
      }
    }
    return nullptr;
  }

  int applyVariant(const char *const name, const char *const src, char *const dst, int dstCapacity)
  {
    const VariantEntry *const entry = findVariant(name);
    if (entry == nullptr) {
      return -1;
    }
    return entry->apply(src, dst, dstCapacity);
  }
}
