
#include "bozWebsocketClient.h"
#include "bozWsClient_p.h"

namespace BOZ {
    
qint64 bozWebsocketClientPrivate::write(const char *data, qint64 max) {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    QByteArray a(data, max);
    _wdata << a;
    libwebsocket_callback_on_writable(context, getWsi(0));
    return max;    
} 

qint64 bozWebsocketClientPrivate::write(const QByteArray &a) {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    _wdata << a;
    libwebsocket_callback_on_writable(context, getWsi(0));
    return a.size();    
}
        
} // NAMESPACE
