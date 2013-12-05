
#include "bozWebsocketClient.h"
#include "bozWsClient_p.h"

namespace BOZ {
    
bozWebsocketClient::bozWebsocketClient(QObject *parent) : 
    QObject(parent), d_ptr(new bozWebsocketClientPrivate(this)) {
//    qDebug("%s: this (%p)", __PRETTY_FUNCTION__, this);
//     Q_D(bozWebsocketClient);
}
    
bozWebsocketClient::~bozWebsocketClient() {
//    qDebug("%s: this (%p)", __PRETTY_FUNCTION__, this);
    if(d_ptr)
        delete d_ptr;    
}

} // NAMESPACE
