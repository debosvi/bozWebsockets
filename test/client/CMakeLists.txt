
set(WS_TEST_CLIENT test-client)

QT5_WRAP_CPP(HEADERS_MOC main.h)
add_executable(${WS_TEST_CLIENT} ${HEADERS_MOC} main.cpp)
target_link_libraries(${WS_TEST_CLIENT}
    bozWsClient
    )
