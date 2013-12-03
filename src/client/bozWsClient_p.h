
#ifndef _QRTD_PROOF_PRIVATE_H_
#define _QRTD_PROOF_PRIVATE_H_

#include <QtCore>
#include "bozWsClient_p.h"

namespace BOZ {

class bozWebsocketClient;

class bozWebsocketClientPrivate : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(bozWebsocketClientPrivate)
    Q_DECLARE_PUBLIC(bozWebsocketClient)

public:
    bozWebsocketClientPrivate(bozWebsocketClient *p, QObject *parent=0);
    ~bozWebsocketClientPrivate();

Q_SIGNALS:


private:
    bozWebsocketClient * const q_ptr;
    QString* _uri;
    qint64 _port;

};

}

#endif // _QRTD_PROOF_PRIVATE_H_
