
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(BOZ_WS_CLIENT_LIB bozWsClient)

set(BOZ_WS_CLIENT_HDRS 
    ${PROJECT_SOURCE_DIR}/include/bozWebsocketClient.h
    bozWsClient_p.h
    )

set(BOZ_WS_CLIENT_SRCS 
    bozWsClient_p.cpp
    bozWsConstructor.cpp
    bozWsConnect.cpp
    )

QT5_WRAP_CPP(${BOZ_WS_CLIENT_LIB}_HEADERS_MOC ${BOZ_WS_CLIENT_HDRS})

add_library(${BOZ_WS_CLIENT_LIB} SHARED
    ${${BOZ_WS_CLIENT_LIB}_HEADERS_MOC}
    ${BOZ_WS_CLIENT_SRCS}
    )
    
target_link_libraries(${BOZ_WS_CLIENT_LIB} 
    ${Qt5Network_LIBRARIES}
    websockets
    )