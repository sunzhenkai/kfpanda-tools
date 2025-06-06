cmake_minimum_required(VERSION 3.20)
project(kfpanda-tools)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-Wall)
include(GNUInstallDirs) # CMAKE_INSTALL_INCLUDEDIR / CMAKE_INSTALL_LIBDIR / ...

if(BUILD_TESTING)
  # set testing install prefix
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build/install/)
endif()

# 3rd packages
find_package(fmt CONFIG REQUIRED)
find_package(cppcommon CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(kfpanda CONFIG REQUIRED)
find_package(unofficial-brpc CONFIG REQUIRED)
find_package(kung-fu-panda-protocols CONFIG REQUIRED)

set(THIRD_LIBRARIES
    kfpanda::kfpanda fmt::fmt cppcommon::cppcommon
    unofficial::brpc::brpc-static
    kung-fu-panda-protocols::kung-fu-panda-protocols)

include_directories(.)
file(GLOB_RECURSE LIB_HREADERS kfpanda/*.h)
file(GLOB_RECURSE LIB_SRCS kfpanda/*.cc)
add_executable(${PROJECT_NAME} cmd/tools.cc ${LIB_HREADERS} ${LIB_SRCS})
target_link_libraries(${PROJECT_NAME} ${THIRD_LIBRARIES})

# install files
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(
  DIRECTORY kfpanda
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING
  PATTERN "*.h")
install(
  EXPORT ${PROJECT_NAME}
  DESTINATION share/${PROJECT_NAME}
  FILE ${PROJECT_NAME}Config.cmake
  NAMESPACE ${PROJECT_NAME}::)
