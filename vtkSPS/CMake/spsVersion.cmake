string(TIMESTAMP timestring %Y%m%d%H%M%S UTC)
set(SPS_MAJOR_VERSION 1)
set(SPS_MINOR_VERSION 0)
set(SPS_PATCH_VERSION 0)
set(SPS_SHORT_VERSION "${SPS_MAJOR_VERSION}.${SPS_MINOR_VERSION}")
set(SPS_VERSION "${SPS_SHORT_VERSION}.${SPS_PATCH_VERSION}")

set(ts_version_suffix "")
if (SPS_VERSIONED_INSTALL)
  set(ts_version_suffix "-${SPS_SHORT_VERSION}")
endif ()

set(SPS_TWEAK_VERSION ${timestring})

