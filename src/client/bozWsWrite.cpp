
#include "bozWebsocketClient.h"
#include "bozWsClient_p.h"

namespace BOZ {
    
qint64 bozWebsocketClient::write(const char *data, qint64 max) {
//    qDebug("%s", __PRETTY_FUNCTION__);
    Q_D(bozWebsocketClient);
    return d->write(data, max);    
} 

qint64 bozWebsocketClient::write(const QByteArray &a) {
//    qDebug("%s", __PRETTY_FUNCTION__);
    Q_D(bozWebsocketClient);
    return d->write(a);    
}
        
} // NAMESPACE
