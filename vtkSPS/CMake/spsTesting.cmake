set(SPS_BUILD_TESTING "OFF"
  CACHE STRING "Build module testing directories")
set_property(CACHE SPS_BUILD_TESTING
  PROPERTY
    STRINGS "ON;OFF;WANT")

if (SPS_BUILD_TESTING)
  include(spsExternalData)

  # Use ctest for dashboard submissions
  include(CTest)
  set_property(CACHE BUILD_TESTING
    PROPERTY
      TYPE INTERNAL)
  set(BUILD_TESTING ON)
else ()
  set(BUILD_TESTING OFF)
endif ()
  
