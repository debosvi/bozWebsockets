
find_package(Qt5Network REQUIRED)
include_directories(${Qt5Network_INCLUDE_DIRS})

add_subdirectory(client)
# add_subdirectory(server)
