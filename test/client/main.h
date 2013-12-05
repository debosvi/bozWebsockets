
#ifndef _MAIN_H_
#define _MAIN_H_

#include "bozWebsocketClient.h"

class TestWs : public QObject{
    Q_OBJECT

public:
    TestWs();
    ~TestWs();
    void connection();
    void disconnection();

private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onData();

private:
    BOZ::bozWebsocketClient* _client;
};

#endif // _MAIN_H_
