
#include "bozWebsocketClient.h"
#include "bozWsClient_p.h"

namespace BOZ {
    
qint64 bozWebsocketClientPrivate::read(char *data, qint64 max) {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    QByteArray a=_data.at(0);
    int lg=a.size();
    if(max>lg)
        lg=max;

    memcpy(data, a.constData(), lg);
    return lg;    
} 

QByteArray bozWebsocketClientPrivate::read() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QMutexLocker locker(&_mutex);
    return _data.takeFirst();    
}
        
} // NAMESPACE
