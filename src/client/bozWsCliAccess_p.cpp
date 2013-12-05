
#include "bozWsClient_p.h"
#include "bozWebsocketClient.h"

namespace BOZ {

int bozWebsocketClientPrivate::getClosed() {
    return was_closed;
}

struct libwebsocket* bozWebsocketClientPrivate::getWsi(int prot) {
    if(!prot)
        return wsi_prot1;
    return NULL;
}

struct libwebsocket_context* bozWebsocketClientPrivate::getContext() {
    return context;
}

void bozWebsocketClientPrivate::storeData(const QByteArray &a) {
    _data << a;
    Q_EMIT q_ptr->readyRead();
}
          
} // NAMESPACE
