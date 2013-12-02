/**
 * \file bozWebsocketClient.h
 * \defgroup BOZ_WEBSOCKET Boz Websocket Client API
 * @{
 */

#ifndef _BOZ_WEBSOCKET_CLIENT_H_
#define _BOZ_WEBSOCKET_CLIENT_H_

#include <QtNetwork>

namespace BOZ {
    
class bozWebsocketClient : public QObject {
    Q_OBJECT
    
public:
    bozWebsocketClient(QObject *parent=0);
    ~bozWebsocketClient();
    virtual void connectToHost(const QHostAddress & address, quint16 port);    
    virtual void disconnectFromHost();
    
private:
    int _fd;
};

} // NAMESPACE

#endif // _BOZ_WEBSOCKET_CLIENT_H_

/**
 * @}
 */
