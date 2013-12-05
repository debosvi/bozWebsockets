
#ifndef _QBOZWSTHREAD_H_
#define _QBOZWSTHREAD_H_

#include <QtCore>

#include "bozWsClient_p.h"
#include "libwebsockets.h"

namespace BOZ {

class bozWebsocketThread : public QThread {
    Q_OBJECT
    
public:
    explicit bozWebsocketThread(bozWebsocketClientPrivate *p);
    ~bozWebsocketThread();
    void quit();
    
Q_SIGNALS:

private:
    virtual void run();

private:
    bozWebsocketClientPrivate *_owner;
    int _quit;
};

}

#endif // _QBOZWSTHREAD_H_
