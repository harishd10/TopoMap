find_package(Boost REQUIRED)

add_executable(TopoMapExample main.cpp)

if(NOT MSVC)
    find_package(OpenMP REQUIRED)
    target_link_libraries(TopoMapExample PRIVATE OpenMP::OpenMP_CXX)
endif()

target_link_libraries(TopoMapExample
    PRIVATE
        TopoMap
        Boost::boost
)
