
#include "bozWsClient_p.h"
#include "bozWebsocketClient.h"
#include "bozWsThread.h"

namespace BOZ {

const qint8 bozWebsocketClientPrivate::MaxProtocolLength = BOZ_WS_PROT_MAX;

bozWebsocketClientPrivate::bozWebsocketClientPrivate(const QString &protocol, bozWebsocketClient *p, QObject *parent) : 
    QObject(parent), q_ptr(p),
    _mutex(QMutex::Recursive), _thread(Q_NULLPTR), 
    context(Q_NULLPTR), wsi_prot1(Q_NULLPTR),
    was_quit(0), was_closed(0), deny_deflate(0), deny_mux(0)
    {

    memset(_prot, 0, bozWebsocketClientPrivate::MaxProtocolLength);
    strncpy(_prot, protocol.toLatin1().constData(), bozWebsocketClientPrivate::MaxProtocolLength);
    if(protocol.size() > bozWebsocketClientPrivate::MaxProtocolLength)
        qDebug("%s: protocol truncated to (%s)", __PRETTY_FUNCTION__, _prot);
} 

bozWebsocketClientPrivate::~bozWebsocketClientPrivate() {
//    qDebug("%s: this (%p)", __PRETTY_FUNCTION__, this);

    if(wsi_prot1)
        disconnectFromHost();
    
    if(context)
        libwebsocket_context_destroy(context);    

    if(_thread)
        delete _thread; 
} 

} // NAMESPACE
