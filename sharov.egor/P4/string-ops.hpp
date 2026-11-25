#ifndef STRING_OPS_HPP
#define STRING_OPS_HPP

namespace sharov {
  int spcRmv(const char *src, char *dst, int dstCapacity);
  int decRmv(const char *src, char *dst, int dstCapacity);
  int latRmv(const char *src, char *dst, int dstCapacity);
  int cmnSym(const char *src, char *dst, int dstCapacity);
  int uncSym(const char *src, char *dst, int dstCapacity);
  int repSym(const char *src, char *dst, int dstCapacity);
  int difLat(const char *src, char *dst, int dstCapacity);
  int hasRep(const char *src, char *dst, int dstCapacity);
  int seqSym(const char *src, char *dst, int dstCapacity);
  int rplSym(const char *src, char *dst, int dstCapacity);
  int uppLow(const char *src, char *dst, int dstCapacity);
  int uniTwo(const char *src, char *dst, int dstCapacity);
  int hasSam(const char *src, char *dst, int dstCapacity);
  int shrSym(const char *src, char *dst, int dstCapacity);
  int excSnd(const char *src, char *dst, int dstCapacity);
  int dgtSnd(const char *src, char *dst, int dstCapacity);
  int repDgt(const char *src, char *dst, int dstCapacity);
  int rmvVow(const char *src, char *dst, int dstCapacity);
  int frqTop(const char *src, char *dst, int dstCapacity);
  int latTwo(const char *src, char *dst, int dstCapacity);
}

#endif
