string(TIMESTAMP timestring %Y%m%d%H%M%S UTC)
set(TS_MAJOR_VERSION 1)
set(TS_MINOR_VERSION 0)
set(TS_PATCH_VERSION 0)
set(TS_SHORT_VERSION "${TS_MAJOR_VERSION}.${TS_MINOR_VERSION}")
set(TS_VERSION "${TS_SHORT_VERSION}.${TS_PATCH_VERSION}")

set(ts_version_suffix "")
if (TS_VERSIONED_INSTALL)
  set(ts_version_suffix "-${TS_SHORT_VERSION}")
endif ()

set(TS_TWEAK_VERSION ${timestring})

