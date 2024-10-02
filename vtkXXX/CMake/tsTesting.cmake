set(TS_BUILD_TESTING "OFF"
  CACHE STRING "Build module testing directories")
set_property(CACHE TS_BUILD_TESTING
  PROPERTY
    STRINGS "ON;OFF;WANT")

if (TS_BUILD_TESTING)
  # TODO: Figure out if we want to use ExternalData 
  # include(tsExternalData)

  # Use ctest for dashboard submissions
  include(CTest)
  set_property(CACHE BUILD_TESTING
    PROPERTY
      TYPE INTERNAL)
  set(BUILD_TESTING ON)
else ()
  set(BUILD_TESTING OFF)
endif ()
  
