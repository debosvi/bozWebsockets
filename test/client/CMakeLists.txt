
set(WS_TEST_CLIENT test-client)

add_executable(${WS_TEST_CLIENT} main.cpp)
target_link_libraries(${WS_TEST_CLIENT}
    bozWsClient
    )