
#include "bozWsThread.h"
#include "libwebsockets.h"

namespace BOZ {

bozWebsocketThread::bozWebsocketThread(bozWebsocketClientPrivate *p) : 
    QThread(p), _owner(p), _quit(0) {
//    qDebug("%s", __PRETTY_FUNCTION__);
}

bozWebsocketThread::~bozWebsocketThread() {
//    qDebug("%s", __PRETTY_FUNCTION__);

}

void bozWebsocketThread::quit() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    _quit=1;
    QThread::quit();
}

void bozWebsocketThread::run() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    
    struct libwebsocket_context *context = _owner->getContext();
  //  qDebug("%s: context(%p)", __PRETTY_FUNCTION__, context);

    _quit=0;

    while(!_quit || !_owner->getClosed()) {
//        qDebug("%s: quit(%d), closed(%d)", __PRETTY_FUNCTION__, _quit, _owner->getClosed());
        if(_quit==1) {
            _quit++;
            qDebug("%s: last chance to kill context, should call CALLBACK_CLOSED soon", __PRETTY_FUNCTION__);
            libwebsocket_callback_on_writable(context, _owner->getWsi(0));
        }
 
//        qDebug("%s: loop", __PRETTY_FUNCTION__);

        int n=libwebsocket_service(context, 10);
        if(n<0) {
            qDebug("%s: libwebsocket_service failed!!", __PRETTY_FUNCTION__);
            continue;
        }

        
 
    }
//    qDebug("%s: terminate", __PRETTY_FUNCTION__);
  //  qDebug("%s: quit(%d), closed(%d)", __PRETTY_FUNCTION__, _quit, _owner->getClosed());

}

} // NAMESPACE

