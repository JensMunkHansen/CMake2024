#include "Foo.h"
#include "config.h"
#include <malloc.h>

namespace Library
{
void SqrtArray(const float* pInput, const size_t nInput, size_t* nOutput, float** pOutput)
{
  *nOutput = nInput;
  *pOutput = (float*)malloc(nInput * sizeof(float));

  for (size_t i = 0; i < nInput; i++)
  {
    *pOutput[i] = pInput[i];
  }
}
const char* Version()
{
  return LIBRARY_VERSION_STRING;
}
}
