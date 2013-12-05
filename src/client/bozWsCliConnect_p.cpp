
#include "bozWsClient_p.h"
#include "bozWebsocketClient.h"
#include "bozWsThread.h"

namespace BOZ {

void bozWebsocketClientPrivate::disconnectFromHost() {
//    qDebug("%s", __PRETTY_FUNCTION__);

    if(_thread && wsi_prot1) {
        QEventLoop ev(this);

        connect(_thread, SIGNAL(finished()), &ev, SLOT(quit()));
        _thread->quit();
        was_quit=1;
        ev.exec();
        wsi_prot1=Q_NULLPTR;
    }
//    Q_EMIT disconnected();
}

void bozWebsocketClientPrivate::connectToHost(const QHostAddress & address, quint16 port) {
    struct lws_context_creation_info info;
    int idx=0;
//    qDebug("%s: address (%s), port(%d)", __PRETTY_FUNCTION__, address.toString().toLatin1().constData(), port); 
    
//     protocols[idx].name = "http-only";
//     protocols[idx].callback = prot0;
//     protocols[idx].per_session_data_size = sizeof(bozWsPrivate_t);
//     protocols[idx++].rx_buffer_size = 20;

    if(!context) {
        protocols[idx].name = "dumb-increment-protocol";
        protocols[idx].callback = prot0;
        protocols[idx].per_session_data_size = sizeof(bozWsPrivate_t);
        protocols[idx++].rx_buffer_size = 128;
        
        memset(&info, 0, sizeof(struct lws_context_creation_info));
        info.port = 0;
        info.protocols = protocols;
        info.gid = -1;
        info.uid = -1;
        info.user = this;

        context = libwebsocket_create_context(&info);

        if (!context) {
            qDebug("%s: Creating libwebsocket context failed", __PRETTY_FUNCTION__);
            Q_EMIT q_ptr->error(QAbstractSocket::UnknownSocketError);
            return;
        }
    }
    
    if(wsi_prot1) {
        qDebug("%s: should disconnect previously, already connected", __PRETTY_FUNCTION__);
        Q_EMIT q_ptr->error(QAbstractSocket::UnknownSocketError);
        return;
    }

    wsi_prot1 = libwebsocket_client_connect(context, address.toString().toLatin1().constData(), port, 0,
                                            "/", address.toString().toLatin1().constData(), address.toString().toLatin1().constData(),
                                           protocols[0].name, -1);
    
    if (!wsi_prot1) {
        qDebug("%s: libwebsocket connect failed", __PRETTY_FUNCTION__);
        Q_EMIT q_ptr->error(QAbstractSocket::UnknownSocketError);
        return;
    }


    if(!_thread) {
        _thread = new bozWebsocketThread(this);
    }
    if(!_thread) {
        qDebug("%s: can't instanciate Ws Thread", __PRETTY_FUNCTION__);
        Q_EMIT q_ptr->error(QAbstractSocket::UnknownSocketError);
        return;
    }

    was_quit=was_closed=0;
    if(!_thread->isRunning())
        _thread->start();
    
}

int bozWebsocketClientPrivate::prot0(struct libwebsocket_context *context,
          struct libwebsocket *wsi,
          enum libwebsocket_callback_reasons reason,
          void *user, void *in, size_t len) {

//    qDebug("%s", __PRETTY_FUNCTION__);
    Q_UNUSED(context)
    Q_UNUSED(wsi)
    
    bozWsPrivate_t *p_user = (bozWsPrivate_t*)user;
 //   qDebug("private user (%p)", p_user);
    
    switch (reason) {
        
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            qDebug("callback_dumb_increment: LWS_CALLBACK_CLIENT_ESTABLISHED");
            p_user->priv = (BOZ::bozWebsocketClientPrivate*)libwebsocket_context_user(context);
            p_user->wsi = wsi;
            //qDebug("private ref (%p)", p_user->priv);
            //qDebug("q_ptr (%p)", p_user->priv->q_ptr);
            Q_EMIT p_user->priv->q_ptr->connected();
            break;
            
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            qDebug("LWS_CALLBACK_CLIENT_CONNECTION_ERROR");
            p_user->priv->was_closed = 1;
            break;
            
        case LWS_CALLBACK_CLOSED:
            qDebug("LWS_CALLBACK_CLOSED");
   //         qDebug("private ref (%p)", p_user->priv);
     //       qDebug("q_ptr (%p)", p_user->priv->q_ptr);
            p_user->priv->was_closed = 1;
            Q_EMIT p_user->priv->q_ptr->disconnected();
            break;
            
        case LWS_CALLBACK_CLIENT_WRITEABLE:
            qDebug("LWS_CALLBACK_CLIENT_WRITEABLE");
            {
                QByteArray a=p_user->priv->getData();
                int lg=a.size();

                qDebug("LWS_CALLBACK_CLIENT_WRITEABLE: size to send (%d)", lg);
 
                if(a.size()) {
                    char tmp[LWS_SEND_BUFFER_PRE_PADDING + lg + LWS_SEND_BUFFER_POST_PADDING];
                    char *p=&tmp[LWS_SEND_BUFFER_PRE_PADDING];

                    memcpy(p, a.constData(), lg);
                    libwebsocket_write(wsi, (unsigned char *)p, lg, LWS_WRITE_BINARY);
                    qDebug("LWS_CALLBACK_CLIENT_WRITEABLE: data sent");
                }

            }

            if(p_user->priv->hasDataToWrite()) {
                qDebug("LWS_CALLBACK_CLIENT_WRITEABLE: some more data (%d)", p_user->priv->hasDataToWrite());
                libwebsocket_callback_on_writable(context, wsi);
            }

            if(p_user->priv->getQuit())
                return -1;
            break;
            
        case LWS_CALLBACK_CLIENT_RECEIVE:
       //     qDebug("private ref (%p)", p_user->priv);
            //qDebug("rx %d '%s'", (int)len, (char*)in);
            ((char *)in)[len] = '\0';
            {
                QByteArray a((char *)in, (int)len);
                p_user->priv->storeData(a);
            }
            break;
            
        /* because we are protocols[0] ... */
        case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
            if ((strcmp((char*)in, "deflate-stream") == 0) && p_user->priv->deny_deflate) {
                qDebug("denied deflate-stream extension");
                return 1;
            }
            if ((strcmp((char*)in, "deflate-frame") == 0) && p_user->priv->deny_deflate) {
                qDebug("denied deflate-frame extension");
                return 1;
            }
            if ((strcmp((char*)in, "x-google-mux") == 0) && p_user->priv->deny_mux) {
                qDebug("denied x-google-mux extension");
                return 1;
            }
            break;
                
#define CASE_FDS(x) case x: qDebug("LWS_CALLBACK %s", #x); break;

        CASE_FDS(LWS_CALLBACK_ADD_POLL_FD)
        CASE_FDS(LWS_CALLBACK_DEL_POLL_FD)
        CASE_FDS(LWS_CALLBACK_SET_MODE_POLL_FD)
        CASE_FDS(LWS_CALLBACK_CLEAR_MODE_POLL_FD)
        CASE_FDS(LWS_CALLBACK_PROTOCOL_INIT)
        CASE_FDS(LWS_CALLBACK_PROTOCOL_DESTROY)
                
        default:
            qDebug("LWS_CALLBACK default(%d)", reason);
            break;
    }    
    
    return 0;
}
          
} // NAMESPACE
