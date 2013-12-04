
#ifndef _QBOZWEBSOCKETCLIENT_PRIVATE_H_
#define _QBOZWEBSOCKETCLIENT_PRIVATE_H_

#include <QtCore>
#include <QtNetwork>

#include "libwebsockets.h"

namespace BOZ {

class bozWebsocketClient;
class bozWebsocketClientPrivate;
class bozWebsocketThread;
    
typedef struct {
    bozWebsocketClientPrivate* priv;   
} bozWsPrivate_t;

class bozWebsocketClientPrivate : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(bozWebsocketClientPrivate)
    Q_DECLARE_PUBLIC(bozWebsocketClient)
    friend bozWebsocketThread;
    
public:
    explicit bozWebsocketClientPrivate(bozWebsocketClient *p, QObject *parent=Q_NULLPTR);
    ~bozWebsocketClientPrivate();
    void connectToHost(const QHostAddress & address, quint16 port);
    void disconnectFromHost();
    
Q_SIGNALS:

private:
    static int prot0(struct libwebsocket_context *context,
                     struct libwebsocket *wsi,
                     enum libwebsocket_callback_reasons reason,
                     void *user, void *in, size_t len);

protected:
    struct libwebsocket_context* getContext();

private:
    bozWebsocketClient * const q_ptr;
    bozWebsocketThread* _thread;
    struct libwebsocket_protocols protocols[1];
    struct libwebsocket_context *context;
    struct libwebsocket *wsi_prot1;
    int was_closed;
    int deny_deflate;
    int deny_mux;
};

}

#endif // _QBOZWEBSOCKETCLIENT_PRIVATE_H_
