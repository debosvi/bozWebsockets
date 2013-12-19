
#include "bozWebsocketClient.h"
#include "bozWsClient_p.h"

namespace BOZ {
    
bozWebsocketClient::bozWebsocketClient(const QString &protocol, QObject *parent) : 
    QObject(parent), d_ptr(new bozWebsocketClientPrivate(protocol, this, parent)) {
//    qDebug("%s: this (%p)", __PRETTY_FUNCTION__, this);
//     Q_D(bozWebsocketClient);
}
    
bozWebsocketClient::~bozWebsocketClient() {
//    qDebug("%s: this (%p)", __PRETTY_FUNCTION__, this);
    if(d_ptr)
        delete d_ptr;    
}

} // NAMESPACE
