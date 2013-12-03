
#ifndef _QRTD_PROOF_PRIVATE_H_
#define _QRTD_PROOF_PRIVATE_H_

#include <QtCore>
#include <QtNetwork>

#include "bozWsClient_p.h"
#include "libwebsockets.h"

namespace BOZ {

class bozWebsocketClient;
class bozWebsocketClientPrivate;
    
typedef struct {
    bozWebsocketClientPrivate* priv;   
} bozWsPrivate_t;

class bozWebsocketClientPrivate : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(bozWebsocketClientPrivate)
    Q_DECLARE_PUBLIC(bozWebsocketClient)
    
public:
    explicit bozWebsocketClientPrivate(bozWebsocketClient *p, QObject *parent=Q_NULLPTR);
    ~bozWebsocketClientPrivate();
    void connectToHost(const QHostAddress & address, quint16 port);
    
Q_SIGNALS:

private:
    static int prot0(struct libwebsocket_context *context,
                     struct libwebsocket *wsi,
                     enum libwebsocket_callback_reasons reason,
                     void *user, void *in, size_t len);

private:
    bozWebsocketClient * const q_ptr;
    struct libwebsocket_protocols protocols[1];
    struct libwebsocket_context *context;
    struct libwebsocket *wsi_prot1;
    int was_closed;
    int deny_deflate;
    int deny_mux;
};

}

#endif // _QRTD_PROOF_PRIVATE_H_
