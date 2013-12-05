
#include "bozWsClient_p.h"
#include "bozWebsocketClient.h"

namespace BOZ {

int bozWebsocketClientPrivate::getClosed() {
    QMutexLocker locker(&_mutex);
    return was_closed;
}

struct libwebsocket* bozWebsocketClientPrivate::getWsi(int prot) {
    QMutexLocker locker(&_mutex);
    if(!prot)
        return wsi_prot1;
    return NULL;
}

struct libwebsocket_context* bozWebsocketClientPrivate::getContext() {
    QMutexLocker locker(&_mutex);
    return context;
}

void bozWebsocketClientPrivate::storeData(const QByteArray &a) {
    QMutexLocker locker(&_mutex);
    _data << a;
    Q_EMIT q_ptr->readyRead();
}
          
} // NAMESPACE
