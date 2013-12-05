
#include "bozWebsocketClient.h"
#include "bozWsClient_p.h"

namespace BOZ {
    
qint64 bozWebsocketClient::read(char *data, qint64 max) {
//    qDebug("%s", __PRETTY_FUNCTION__);
    Q_D(bozWebsocketClient);
    return d->read(data, max);    
} 

QByteArray bozWebsocketClient::read() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    Q_D(bozWebsocketClient);
    return d->read();    
}
        
} // NAMESPACE
