
#include "bozWebsocketClient.h"
#include "bozWsClient_p.h"

namespace BOZ {
    
bozWebsocketClient::bozWebsocketClient(QObject *parent) : 
    QObject(parent), d_ptr(new bozWebsocketClientPrivate(this)) {
    qDebug("%s", __PRETTY_FUNCTION__);
//     Q_D(bozWebsocketClient);
}
    
bozWebsocketClient::~bozWebsocketClient() {
    qDebug("%s", __PRETTY_FUNCTION__);
    if(d_ptr)
        delete d_ptr;    
}

} // NAMESPACE
