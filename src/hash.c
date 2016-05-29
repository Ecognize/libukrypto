#include "libdstu4145.h"
#include <string.h>

size_t dstu4145_hashlen(const uint8_t *iH, size_t LiH)
{
  /* FIXME: only ГОСТ 34.311 standard function supported for now */
  if (LiH != dstu4145_defaultLiH || memcmp(iH, dstu4145_defaultiH, LiH))
    return 0;
  else
    return 32;
}

bool dstu4145_hashmessage(const uint8_t *T, size_t LT, const uint8_t *iH, size_t LiH, uint8_t *HT, size_t LH)
{
  /* FIXME: only ГОСТ 34.311 standard function supported for now */
  if (LiH != dstu4145_defaultLiH || memcmp(iH, dstu4145_defaultiH, LiH))
    return false;

  /* Check for storage requirements */
  if (LH < dstu4145_hashlen(iH, LiH))
    return false;

  return true;
}
