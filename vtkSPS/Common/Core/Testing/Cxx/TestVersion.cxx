#include "spsVersion.h"
#include "vtkNew.h"
#include "vtkVersion.h"

#include <algorithm>
#include <iostream>
#include <string_view>

int TestVersion(int argc, char* argv[])
{
  int retval;

#if (VTK_VERSION_NUMBER >= VTK_VERSION_CHECK(9, 0, 0))
  retval = EXIT_SUCCESS;
#endif

#if VTK_VERSION_NUMBER <= VTK_VERSION_CHECK(9, 1, 0)
  retval |= EXIT_FAILURE;
#endif

#if SPS_VERSION_NUMBER <= SPS_VERSION_CHECK(0, 9, 0)
  retval |= EXIT_FAILURE;
#endif

#if !(SPS_VERSION_NUMBER >= SPS_VERSION_CHECK(0, 9, 0))
  retval |= EXIT_FAILURE;
#endif
  vtkNew<spsVersion> versionInfo;

  const char* spsVersion = versionInfo->GetSpsVersionFull();

  std::string_view svVersion(spsVersion);

  // Count occurrences of '.' in the string view
  retval |= (std::count(svVersion.begin(), svVersion.end(), '.') - 2);
  return retval;
}
