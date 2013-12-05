
#include "bozWsClient_p.h"
#include "bozWebsocketClient.h"

namespace BOZ {

int bozWebsocketClientPrivate::hasDataToWrite() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    return _wdata.size();
}

int bozWebsocketClientPrivate::getQuit() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    return (was_quit && !_wdata.size());
}

int bozWebsocketClientPrivate::getClosed() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    return was_closed;
}

struct libwebsocket* bozWebsocketClientPrivate::getWsi(int prot) {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    if(!prot)
        return wsi_prot1;
    return NULL;
}

struct libwebsocket_context* bozWebsocketClientPrivate::getContext() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    return context;
}

void bozWebsocketClientPrivate::storeData(const QByteArray &a) {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    _rdata << a;
    Q_EMIT q_ptr->readyRead();
}

QByteArray bozWebsocketClientPrivate::getData() {
    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    if(!_wdata.size())
        return QByteArray();

    QByteArray a=_wdata.takeFirst();
    qDebug("%s: exit", __PRETTY_FUNCTION__);
    return a;
}
          
} // NAMESPACE
