
#include "bozWebsocketClient.h"
#include "bozWsClient_p.h"

namespace BOZ {
    
void bozWebsocketClient::connectToHost(const QHostAddress & address, quint16 port) {
    qDebug("%s", __PRETTY_FUNCTION__);
    Q_D(bozWebsocketClient);
    qDebug() << address.toString(); 
    d->connectToHost(address, port);    
    qDebug("%s: exit", __PRETTY_FUNCTION__);
}

void bozWebsocketClient::disconnectFromHost() {
    qDebug("%s", __PRETTY_FUNCTION__);
    Q_D(bozWebsocketClient);
    d->disconnectFromHost();    
    qDebug("%s: exit", __PRETTY_FUNCTION__);
}
        
} // NAMESPACE
