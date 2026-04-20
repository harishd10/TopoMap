find_package(Armadillo REQUIRED)

# MSVC's OpenMP is v2.0; mlpack requires 3.1+. Disable OpenMP on MSVC.
if(NOT MSVC)
    find_package(OpenMP REQUIRED)
endif()

add_library(TopoMap
    TopoMap.cpp
    geomutils.cpp
    DisjointSets.hpp
    TopoMap.hpp
    geomutils.h
)

target_compile_definitions(TopoMap PRIVATE TOPOMAP_LIB)

if(NOT MSVC)
    target_link_libraries(TopoMap PRIVATE OpenMP::OpenMP_CXX)
endif()

target_include_directories(TopoMap
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${ARMADILLO_INCLUDE_DIRS}
)

target_link_libraries(TopoMap
    PRIVATE
        ${ARMADILLO_LIBRARIES}
)

# mlpack is header-only in newer versions; just need include path
find_package(mlpack QUIET)
if(mlpack_FOUND)
    target_link_libraries(TopoMap PRIVATE mlpack::mlpack)
else()
    find_path(MLPACK_INCLUDE_DIR mlpack/core.hpp)
    if(MLPACK_INCLUDE_DIR)
        target_include_directories(TopoMap PRIVATE ${MLPACK_INCLUDE_DIR})
    endif()
endif()
