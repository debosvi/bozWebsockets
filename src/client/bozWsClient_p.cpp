
#include "bozWsClient_p.h"
#include "bozWebsocketClient.h"
#include "bozWsThread.h"

namespace BOZ {

bozWebsocketClientPrivate::bozWebsocketClientPrivate(bozWebsocketClient *p, QObject *parent) : 
    QObject(parent), q_ptr(p), 
    _mutex(QMutex::Recursive), _thread(Q_NULLPTR), 
    context(Q_NULLPTR), wsi_prot1(Q_NULLPTR),
    was_quit(0), was_closed(0), deny_deflate(0), deny_mux(0)
    {
//    qDebug("%s: this (%p)", __PRETTY_FUNCTION__, this);
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
