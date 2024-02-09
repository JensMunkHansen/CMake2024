# Download dependencies by using FetchContent_Declare
# Use FetchContent_MakeAvailable only in those code parts where the dependency is actually needed

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/Thirdparty)

FetchContent_Declare(Catch2
  GIT_REPOSITORY git@github.com:catchorg/Catch2.git
  GIT_TAG v3.5.2
  GIT_SHALLOW ON
  GIT_PROGRESS ON)
FetchContent_MakeAvailable(Catch2)
