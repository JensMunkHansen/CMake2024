#pragma once

#include "foo_export.h"
#include <cstddef>

namespace Library
{
FOO_EXPORT void SqrtArray(
  const float* pInput, const size_t nInput, size_t* nOutput, float** pOutput);
FOO_EXPORT const char* Version();
}
