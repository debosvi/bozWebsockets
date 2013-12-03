
#include "bozWsClient_p.h"

namespace BOZ {

bozWebsocketClientPrivate::bozWebsocketClientPrivate(bozWebsocketClient *pProof, QObject *parent) : 
    QObject(parent), q_ptr(pProof),
    _uri(Q_NULLPTR), _port(80)
    {
    qDebug("%s", __PRETTY_FUNCTION__);
} 

bozWebsocketClientPrivate::~bozWebsocketClientPrivate() {
    qDebug("%s", __PRETTY_FUNCTION__);
    if(_uri)
        delete _uri;
} 

} // NAMESPACE
