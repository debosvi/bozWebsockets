
#include "bozWsClient_p.h"

namespace BOZ {

bozWebsocketClientPrivate::bozWebsocketClientPrivate(bozWebsocketClient *p, QObject *parent) : 
    QObject(parent), q_ptr(p), context(Q_NULLPTR), wsi_prot1(Q_NULLPTR),
    was_closed(0), deny_deflate(0), deny_mux(0)
    {
    qDebug("%s", __PRETTY_FUNCTION__);
} 

bozWebsocketClientPrivate::~bozWebsocketClientPrivate() {
    qDebug("%s", __PRETTY_FUNCTION__);
    
} 

void bozWebsocketClientPrivate::connectToHost(const QHostAddress & address, quint16 port) {
    struct lws_context_creation_info info;
    int idx=0;
    const char *adr=address.toString().toLatin1().constData();
    qDebug("%s", __PRETTY_FUNCTION__);
    
//     protocols[idx].name = "http-only";
//     protocols[idx].callback = prot0;
//     protocols[idx].per_session_data_size = sizeof(bozWsPrivate_t);
//     protocols[idx++].rx_buffer_size = 20;

    protocols[idx].name = "dumb-increment-protocol";
    protocols[idx].callback = prot0;
    protocols[idx].per_session_data_size = sizeof(bozWsPrivate_t);
    protocols[idx++].rx_buffer_size = 128;
        
    memset(&info, 0, sizeof(struct lws_context_creation_info));
    info.port = 0;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;

    context = libwebsocket_create_context(&info);
    if (!context) {
        qDebug("%s: Creating libwebsocket context failed", __PRETTY_FUNCTION__);
        return;
    }
    
    wsi_prot1 = libwebsocket_client_connect(context, adr, port, 0,
                                            "/", adr, adr,
                                           protocols[0].name, -1);
    
    if (!wsi_prot1) {
        qDebug("%s: libwebsocket connect failed", __PRETTY_FUNCTION__);
        return;
    }
}

int bozWebsocketClientPrivate::prot0(struct libwebsocket_context *context,
          struct libwebsocket *wsi,
          enum libwebsocket_callback_reasons reason,
          void *user, void *in, size_t len) {

    qDebug("%s", __PRETTY_FUNCTION__);
    Q_UNUSED(context)
    Q_UNUSED(wsi)
    
    bozWsPrivate_t *p_user = (bozWsPrivate_t*)user;
    
    switch (reason) {
        
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            qDebug("%s: callback_dumb_increment: LWS_CALLBACK_CLIENT_ESTABLISHED", __PRETTY_FUNCTION__);
            break;
            
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            qDebug("%s: LWS_CALLBACK_CLIENT_CONNECTION_ERROR", __PRETTY_FUNCTION__);
            p_user->priv->was_closed = 1;
            break;
            
        case LWS_CALLBACK_CLOSED:
            qDebug("%s: LWS_CALLBACK_CLOSED", __PRETTY_FUNCTION__);
            p_user->priv->was_closed = 1;
            break;
            
        case LWS_CALLBACK_CLIENT_RECEIVE:
            ((char *)in)[len] = '\0';
            qDebug("%s: rx %d '%s'\n", __PRETTY_FUNCTION__, (int)len, (char *)in);
            break;
            
            /* because we are protocols[0] ... */
            
            case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
                if ((strcmp((char*)in, "deflate-stream") == 0) && p_user->priv->deny_deflate) {
                    qDebug("%s: denied deflate-stream extension", __PRETTY_FUNCTION__);
                    return 1;
                }
                if ((strcmp((char*)in, "deflate-frame") == 0) && p_user->priv->deny_deflate) {
                    qDebug("%s: denied deflate-frame extension", __PRETTY_FUNCTION__);
                    return 1;
                }
                if ((strcmp((char*)in, "x-google-mux") == 0) && p_user->priv->deny_mux) {
                    qDebug("%s: denied x-google-mux extension", __PRETTY_FUNCTION__);
                    return 1;
                }
                
                break;
                
            default:
                break;
    }    
    
    return 0;
}
          
} // NAMESPACE
