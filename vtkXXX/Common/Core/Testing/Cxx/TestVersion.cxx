#include "tsVersion.h"
#include "vtkVersion.h"
#include "vtkNew.h"

#include <iostream>
#include <algorithm>
#include <string_view>

int TestVersion(int argc, char* argv[]) {
  int retval;

#if (VTK_VERSION_NUMBER >= VTK_VERSION_CHECK(9, 0, 0))
  retval = EXIT_SUCCESS;
#endif

#if VTK_VERSION_NUMBER <= VTK_VERSION_CHECK(9, 1, 0)
  retval |= EXIT_FAILURE;
#endif

#if TS_VERSION_NUMBER <= TS_VERSION_CHECK(0, 9, 0)
  retval |= EXIT_FAILURE;
#endif

#if !(TS_VERSION_NUMBER >= TS_VERSION_CHECK(0, 9, 0))
  retval |= EXIT_FAILURE;
#endif

  vtkNew<tsVersion> versionInfo;

  const char* tsVersion = versionInfo->GetTsVersionFull();

  std::string_view svVersion(tsVersion);

  // Count occurrences of '.' in the string view
  retval |= (std::count(svVersion.begin(), svVersion.end(), '.') - 2);

  return retval;
}
