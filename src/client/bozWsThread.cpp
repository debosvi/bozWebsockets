
#include "bozWsThread.h"
#include "libwebsockets.h"

namespace BOZ {

bozWebsocketThread::bozWebsocketThread(bozWebsocketClientPrivate *p) : 
    QThread(p), _owner(p) {
    qDebug("%s", __PRETTY_FUNCTION__);
}

bozWebsocketThread::~bozWebsocketThread() {
    qDebug("%s", __PRETTY_FUNCTION__);

}

void bozWebsocketThread::run() {
    qDebug("%s", __PRETTY_FUNCTION__);
    
    struct libwebsocket_context *context = _owner->getContext();
    qDebug("%s: context(%p)", __PRETTY_FUNCTION__, context);
    
    while(!isFinished()) {
//        qDebug("%s: loop", __PRETTY_FUNCTION__);

        int n=libwebsocket_service(context, 10);
        if(n<0) {
            qDebug("%s: libwebsocket_service failed!!", __PRETTY_FUNCTION__);
            continue;
        }

        
 
    }
}

} // NAMESPACE

