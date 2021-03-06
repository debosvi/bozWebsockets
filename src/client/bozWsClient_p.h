
#ifndef _QBOZWEBSOCKETCLIENT_PRIVATE_H_
#define _QBOZWEBSOCKETCLIENT_PRIVATE_H_

#include <QtCore>
#include <QtNetwork>

#include "libwebsockets.h"

namespace BOZ {

#define BOZ_WS_PROT_MAX	64

class bozWebsocketClient;
class bozWebsocketClientPrivate;
class bozWebsocketThread;
    
typedef struct {
    bozWebsocketClientPrivate* priv;   
    struct libwebsocket *wsi;   
} bozWsPrivate_t;

class bozWebsocketClientPrivate : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(bozWebsocketClientPrivate)
    Q_DECLARE_PUBLIC(bozWebsocketClient)
    friend bozWebsocketThread;
    
public:
    explicit bozWebsocketClientPrivate(const QString &protocol, bozWebsocketClient *p, QObject *parent=Q_NULLPTR);
    ~bozWebsocketClientPrivate();
    void connectToHost(const QHostAddress & address, quint16 port);
    void disconnectFromHost();
    qint64 read(char *data, qint64 max);
    QByteArray read();
    qint64 write(const char *data, qint64 max);
    qint64 write(const QByteArray &a);
    
Q_SIGNALS:

private:
    static int prot0(struct libwebsocket_context *context,
                     struct libwebsocket *wsi,
                     enum libwebsocket_callback_reasons reason,
                     void *user, void *in, size_t len);

protected:
    struct libwebsocket_context* getContext();
    int getQuit();
    int hasDataToWrite();
    int getClosed();
    struct libwebsocket *getWsi(int);
    void storeData(const QByteArray &a);
    QByteArray getData();

public:
    static const qint8 MaxProtocolLength;

private:
    bozWebsocketClient * const q_ptr;
    char _prot[BOZ_WS_PROT_MAX];;
    QMutex _mutex;
    QList<QByteArray> _rdata;
    QList<QByteArray> _wdata;
    bozWebsocketThread* _thread;
    struct libwebsocket_protocols protocols[1];
    struct libwebsocket_context *context;
    struct libwebsocket *wsi_prot1;
    int was_quit;
    int was_closed;
    int deny_deflate;
    int deny_mux;
};

}

#endif // _QBOZWEBSOCKETCLIENT_PRIVATE_H_
