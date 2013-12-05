/**
 * \file bozWebsocketClient.h
 * \defgroup BOZ_WEBSOCKET Boz Websocket Client API
 * @{
 */

#ifndef _BOZ_WEBSOCKET_CLIENT_H_
#define _BOZ_WEBSOCKET_CLIENT_H_

#include <QtNetwork>

namespace BOZ {
    
class bozWebsocketClientPrivate;    
    
class bozWebsocketClient : public QObject {
    Q_OBJECT
    
public:
    explicit bozWebsocketClient(QObject *parent=Q_NULLPTR);
    ~bozWebsocketClient();
    virtual void connectToHost(const QHostAddress & address, quint16 port);    
    virtual void disconnectFromHost();
    qint64 read(char *data, qint64 max);
    QByteArray read();
    qint64 write(const char *data, qint64 max);
    qint64 write(const QByteArray &a);

Q_SIGNALS:
    void connected();
    void disconnected();
    void readyRead();
    void bytesWritten(qint64);
    void error(QAbstractSocket::SocketError);
    
private:
    bozWebsocketClientPrivate* const d_ptr;
    Q_DECLARE_PRIVATE(bozWebsocketClient)
    Q_DISABLE_COPY(bozWebsocketClient)
};

} // NAMESPACE

#endif // _BOZ_WEBSOCKET_CLIENT_H_

/**
 * @}
 */
